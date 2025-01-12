#include "FlightDatabase.h"
#include <exception>

/*
    Compile:
    g++ -std=c++11 airplane_db.cpp -lsqlite3 -o airplane_db

*/

/*
TODO: Better concurrency control, + start using atomic and condition_variable
*/

FlightDatabase::FlightDatabase(const char* dbname) {
    if (sqlite3_open(dbname, &(self.db)) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(self.db) << std::endl;
        return;
    }
    sqlite3_exec(self.db, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
    sqlite3_exec(self.db, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);
    
    if (setSchema() != SQLITE_OK){
        std::cerr << "Can't define database: " << sqlite3_errmsg(self.db) << std::endl;
        return;
    }

    self.last_trans = std::chrono::steady_clock::now();

    createStatements();
}

FlightDatabase::~FlightDatabase() {
    finalizeStatements();
    sqlite3_close(self.db);
}

bool FlightDatabase::setSchema() {    
    char* errMsg = nullptr;
    for (int i = 0; i < num_tables; i++) {
        int rc = sqlite3_exec(self.db, db_create_table_transactions[i], nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return rc;
        }
    }
    std::cout << "Database schema created successfully" << std::endl;
    return SQLITE_OK;
}

/*
TODO: Find new features to implement
*/
void FlightDatabase::DB_loop() {
    // If binded_stmt_queue is empty, return
    if (DB->binded_stmt_queue.empty()) {return;}

    // Get time elapsed since last query
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - self.last_trans).count();

    // If enough logs (or elapsed time) to process, process them
    if (DB->binded_stmt_queue.size() > TRANSACTION_MIN_BATCH_SIZE || elapsed_time > TRANSACTION_MAX_DELAY_MS) {
        // If transaction fails
        if( DB->executeTransaction()){ std::cout << "Transaction failed" << std::endl; }
/*
TODO: Find something to do ...
*/
    }
}

void FlightDatabase::createStatements() {
    // For each queue in the free_stmt_queues
    for (int i = 0; i < NUM_SQL_DB_TABLES; i++) {       // 9
        // For each slot in queue
        while(!free_stmt_queues[i].full()) {
            // 1) Declare & Prepare
            sqlite3_stmt* stmt; 
            sqlite3_prepare_v2(db, sql_atc_system, -1, &stmt, NULL);
            // 2) Enqueue
            free_stmt_queues[i].enqueue();
        }         
    }
}

void FlightDatabase::finalizeStatements() {
    // For each queue in the free_stmt_queues
    for (int i = 0; i < NUM_SQL_DB_TABLES; i++) {       // 9
        // For each statement in queue
        while(!free_stmt_queues[i].empty()) {
            sqlite3_stmt* stmt = free_stmt_queues[i].dequeue();
            sqlite3_finalize(stmt);
        }         
    }
}

void FlightDatabase::beginTransaction() {
    char* errMsg = nullptr;
    sqlite3_exec(self.db, "BEGIN TRANSACTION", NULL, NULL, &errMsg);
}

// Success -> false
bool FlightDatabase::executeTransaction() {
    // Begin transaction
    if (sqlite3_exec(self.db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to begin transaction: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    // Execute statements in 1 batch
    int transactions_sent = 0;
    while (!binded_sql_stmt.empty() && transactions_sent < TRANSACTION_MAX_BATCH_SIZE) {
        try{
            char* errMsg = nullptr;
            DbStatement lr = binded_sql_stmt.dequeue();
            sqlite3_stmt* stmt = lr.stmt;
            // Execute the statement
            int result = sqlite3_step(stmt);
            if (result != SQLITE_DONE) {
                std::cout << "Failed to execute statement: " << sqlite3_errmsg(self.db) << std::endl;
                throw exception("SQL execution failed");
            }
            // Reset the statement
            if (sqlite3_reset(stmt) != SQLITE_OK) {
                std::cout << "Failed to reset statement: " << sqlite3_errmsg(self.db) << std::endl;
                throw exception("SQL reset failed");
            }
            // Commit the transaction
            if (sqlite3_exec(self.db, "COMMIT", nullptr, nullptr, &errMsg) != SQLITE_OK) {
                std::cout << "Failed to commit transaction: " << sqlite3_errmsg(self.db) << std::endl;
                throw exception("SQL commit failed");
            }
            // Complete the transaction        
            // 1) Recycle the statement
            /*
            TODO: At runtime verify the reference technique is proper
            */   
            free_stmt_queue[lr.table].enqueue(lr);
            // 2) Update the last transaction time
            self.last_trans = std::chrono::steady_clock::now();
            // 3) Update the transaction count
            transactions_sent++;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            db.rollbackTransaction();
            return true;
        }
    }
    return false;
}

void FlightDatabase::rollbackTransaction() {
    char* errMsg = nullptr;
    sqlite3_exec(self.db, "ROLLBACK", nullptr, nullptr, &errMsg);
}

int64_t FlightDatabase::getCurrentTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

// Success -> true    // Used to log by outsiders during operations
bool FlightDatabase::insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active) {
// 1) Check if the queue is empty
    if (free_atc_system_stmt_queue.empty()){ 
        std::cout << "free_atc_system_stmt_queue is empty" << std::endl;
        return false;
    }
// 2) Create a new LogRecord with a free statement
    DbStatement lr(StatementType::ATC_SYSTEM, free_atc_system_stmt_queue.dequeue());
// 3)Bind values
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_int(lr.stmt, 2, ctlr_paired);
    sqlite3_bind_int(lr.stmt, 3, rf_rx_active);
    sqlite3_bind_int(lr.stmt, 4, rf_tx_active);
// 4) Enqueue the LogRecord for execution
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertSystemStatus(int control_mode, bool paired, bool throttle_lock, 
                        bool holding_pattern, bool taxi_only, bool gps_active) {
    if (free_system_status_stmt_queue.empty()) {
        std::cout << "free_system_status_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::SYSTEM_STATUS, free_system_status_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_int(lr.stmt, 2, control_mode);
    sqlite3_bind_int(lr.stmt, 3, paired);
    sqlite3_bind_int(lr.stmt, 4, throttle_lock);
    sqlite3_bind_int(lr.stmt, 5, holding_pattern);
    sqlite3_bind_int(lr.stmt, 6, taxi_only);
    sqlite3_bind_int(lr.stmt, 7, gps_active);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertFlightStatus(double battery_level, double signal_strength, bool flying) {
    if (free_flight_status_stmt_queue.empty()) {
        std::cout << "free_flight_status_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::FLIGHT_STATUS, free_flight_status_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, battery_level);
    sqlite3_bind_double(lr.stmt, 3, signal_strength);
    sqlite3_bind_int(lr.stmt, 4, flying);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertFlightVars(double pitch, double roll, double yaw, double distance) {
    if (free_flight_vars_stmt_queue.empty()) {
        std::cout << "free_flight_vars_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::FLIGHT_VARS, free_flight_vars_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, pitch);
    sqlite3_bind_double(lr.stmt, 3, roll);
    sqlite3_bind_double(lr.stmt, 4, yaw);
    sqlite3_bind_double(lr.stmt, 5, distance);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertServos(int throttle, int elevator, int rudder, int left_aileron, int right_aileron) {
    if (free_servos_stmt_queue.empty()) {
        std::cout << "free_servos_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::SERVOS, free_servos_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_int(lr.stmt, 2, throttle);
    sqlite3_bind_int(lr.stmt, 3, elevator);
    sqlite3_bind_int(lr.stmt, 4, rudder);
    sqlite3_bind_int(lr.stmt, 5, left_aileron);
    sqlite3_bind_int(lr.stmt, 6, right_aileron);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength) {
    if (free_gps_data_stmt_queue.empty()) {
        std::cout << "free_gps_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::GPS_DATA, free_gps_data_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, latitude);
    sqlite3_bind_double(lr.stmt, 3, longitude);
    sqlite3_bind_double(lr.stmt, 4, altitude);
    sqlite3_bind_double(lr.stmt, 5, speed);
    sqlite3_bind_int(lr.stmt, 6, satellites);
    sqlite3_bind_int(lr.stmt, 7, signal_strength);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z) {
    if (free_imu_data_stmt_queue.empty()) {
        std::cout << "free_imu_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::IMU_DATA, free_imu_data_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, accel_x);
    sqlite3_bind_double(lr.stmt, 3, accel_y);
    sqlite3_bind_double(lr.stmt, 4, accel_z);
    sqlite3_bind_double(lr.stmt, 5, gyro_x);
    sqlite3_bind_double(lr.stmt, 6, gyro_y);
    sqlite3_bind_double(lr.stmt, 7, gyro_z);
    sqlite3_bind_double(lr.stmt, 8, mag_x);
    sqlite3_bind_double(lr.stmt, 9, mag_y);
    sqlite3_bind_double(lr.stmt, 10, mag_z);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertBaroData(double pressure, double temperature, double calculated_altitude) {
    if (free_baro_data_stmt_queue.empty()) {
        std::cout << "free_baro_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::BARO_DATA, free_baro_data_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, pressure);
    sqlite3_bind_double(lr.stmt, 3, temperature);
    sqlite3_bind_double(lr.stmt, 4, calculated_altitude);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d) {
    if (free_pid_data_stmt_queue.empty()) {
        std::cout << "free_pid_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::PID_DATA, free_pid_data_stmt_queue.dequeue());
    int64_t timestamp = getCurrentTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, roll_p);
    sqlite3_bind_double(lr.stmt, 3, roll_i);
    sqlite3_bind_double(lr.stmt, 4, roll_d);
    sqlite3_bind_double(lr.stmt, 5, yaw_p);
    sqlite3_bind_double(lr.stmt, 6, yaw_i);
    sqlite3_bind_double(lr.stmt, 7, yaw_d);
    sqlite3_bind_double(lr.stmt, 8, pitch_p);
    sqlite3_bind_double(lr.stmt, 9, pitch_i);
    sqlite3_bind_double(lr.stmt, 10, pitch_d);
    binded_stmt_queue.enqueue(lr);
    return true;
}


