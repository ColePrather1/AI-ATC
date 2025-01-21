
#include "FlightDatabase.h"
//#include <exception>
#include "Schema.h"

#include "Session.h"
#include "myTime.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "ThreadSafeQueue.h"


/*
    Compile:
    g++ -std=c++11 airplane_db.cpp -lsqlite3 -o airplane_db

*/

/*
TODO: Better concurrency control, + start using atomic and condition_variable
*/

FlightDatabase::FlightDatabase(std::string dbname) {
    if (sqlite3_open(dbname.c_str(), &(db)) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_exec(db, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
    sqlite3_exec(db, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);
    
    if (setSchema() != SQLITE_OK){
        std::cerr << "Can't define database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    last_trans = std::chrono::steady_clock::now();

    free_stmt_queues[0] = &free_plane_state_stmt_queue;
    free_stmt_queues[1] = &free_servo_data_stmt_queue;
    free_stmt_queues[2] = &free_gps_data_stmt_queue;
    free_stmt_queues[3] = &free_gps_env_data_stmt_queue;
    free_stmt_queues[4] = &free_accel_data_stmt_queue;
    free_stmt_queues[5] = &free_gyro_data_stmt_queue;
    free_stmt_queues[6] = &free_mag_data_stmt_queue;
    free_stmt_queues[7] = &free_baro_data_stmt_queue;
    free_stmt_queues[8] = &free_pid_data_stmt_queue;
    free_stmt_queues[9] = &free_event_log_stmt_queue;

    //binded_stmt_queue = ThreadSafeQueue<DbStatement>(50);

    //Session::logger_thread_active.store(true, std::memory_order_release);

    createStatements();
    //Session::getInstance().setDatabase(this);
    Session::logger_started.store(true, std::memory_order_release);
    return;
}

/*
FlightDatabase::FlightDatabase(const char* dbname) {
    if (sqlite3_open(dbname, &(db)) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_exec(db, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
    sqlite3_exec(db, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);
    
    if (setSchema() != SQLITE_OK){
        std::cerr << "Can't define database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    last_trans = std::chrono::steady_clock::now();

    free_stmt_queues[0] = &free_plane_state_stmt_queue;
    free_stmt_queues[1] = &free_servo_data_stmt_queue;
    free_stmt_queues[2] = &free_gps_data_stmt_queue;
    free_stmt_queues[3] = &free_gps_env_data_stmt_queue;
    free_stmt_queues[4] = &free_accel_data_stmt_queue;
    free_stmt_queues[5] = &free_gyro_data_stmt_queue;
    free_stmt_queues[6] = &free_mag_data_stmt_queue;
    free_stmt_queues[7] = &free_baro_data_stmt_queue;
    free_stmt_queues[8] = &free_pid_data_stmt_queue;
    free_stmt_queues[9] = &free_event_log_stmt_queue;

    //binded_stmt_queue = ThreadSafeQueue<DbStatement>(50);

    createStatements();
}

*/

FlightDatabase::~FlightDatabase() {
    //finalizeStatements();
    //sqlite3_close(db);
    stopDBLoop();
}

bool FlightDatabase::setSchema() {    
    char* errMsg = nullptr;
    for (int i = 0; i < NUM_SQL_DB_TABLES; i++) {
        int rc = sqlite3_exec(db, db_create_table_transactions[i], nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return rc;
        }
        //std::cout << "Table " << i << " created successfully" << std::endl;
    }
    std::cout << "Database schema created successfully" << std::endl;
//TODO: DEV
    //insertEventLog(EventType::DB_CREATED, myTime::getTimestamp(), 0);
    return SQLITE_OK;
}

void FlightDatabase::startDBLoop() {
    //Session::logger_thread_active.store(true, std::memory_order_release);
    
    // Wait for logging setup to finish, prior to starting main DB loop
    while (!Session::logger_started.load(std::memory_order_acquire) 
    && !Session::quit_flag.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };

    DB_thread = std::thread(&FlightDatabase::DB_loop, this);
    //Session::logger_started.store(true, std::memory_order_release);
    //Session::logger_thread_active.store(true, std::memory_order_release);
    // TODO: decide about detach()
    //DB_thread.detach();
    //Session::logger_running.store(true, std::memory_order_release);
    //Session::logger_loop_active.store(true, std::memory_order_release);
    return;
}

void FlightDatabase::stopDBLoop() {
    //while(binded_stmt_queue.size() > 0) {
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    //} // Wait for queue to empty
    Session::logger_loop_active.store(false, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //Session::logger_running.store(false, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //DB_loop_active = false;
    // TODO: decide about detach() affects this

    if (!Session::sql_finalized.load(std::memory_order_acquire)) {
        finalizeStatements();
        Session::sql_finalized.store(true, std::memory_order_release);
    }

    if (!Session::sql_closed.load(std::memory_order_acquire)) {
        sqlite3_close(db);
        Session::sql_closed.store(true, std::memory_order_release);
    }


    if (DB_thread.joinable()) {
        DB_thread.join();
        //Session::logger_thread_active.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //Session::logger_running.store(false, std::memory_order_release);
        std::cout << "Logging Thread finished successfully." << std::endl;
    }
    Session::logger_finished.store(true, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return;
}

/*
TODO: Find new features to implement
*/
void FlightDatabase::DB_loop() {
    Session::logger_loop_active.store(true, std::memory_order_release);
    while (Session::logger_loop_active.load(std::memory_order_relaxed)) {
        // If binded_stmt_queue is empty, return
        if (binded_stmt_queue.empty()) {
//TODO: DEV 
            //std::cout << "binded_stmt_queue is empty" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //insertEventLog(EventType::DB_LOOPED, myTime::getTimestamp(), 0);
            continue;
        }
        // Get time elapsed since last query
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_trans).count();

        // If enough logs (or elapsed time) to process, process them
        if (binded_stmt_queue.getSize() > TRANSACTION_MIN_BATCH_SIZE || elapsed_time > TRANSACTION_MAX_DELAY_MS) {
            // If transaction fails
            if( executeTransaction()){ std::cout << "Transaction failed" << std::endl; }
            // TODO: Find something to do ...
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Prevent busy-waiting
    }
}

void FlightDatabase::createStatements() {
    // For each queue in the free_stmt_queues
    for (int i = 0; i < NUM_SQL_DB_TABLES; i++) {       // 9
        // For each slot in queue
        //std::cout << "Creating " << sql_create_statements[i] << std::endl;
        while(!free_stmt_queues[i]->isFull()) {
            // 1) Declare & Prepare
            sqlite3_stmt* stmt; 
            sqlite3_prepare_v2(db, sql_create_statements[i], -1, &stmt, NULL);
            //sqlite3_prepare_v2(db, sql_atc_system, -1, &stmt, NULL);
            // 2) Enqueue
            free_stmt_queues[i]->enqueue(stmt);
        }         
    }
    std::cout << "Statements created successfully" << std::endl;
}

void FlightDatabase::finalizeStatements() {
    // For each queue in the free_stmt_queues
    for (int i = 0; i < NUM_SQL_DB_TABLES; i++) {       // 9
        // For each statement in queue
        while(!free_stmt_queues[i]->empty()) {
            sqlite3_stmt* stmt = free_stmt_queues[i]->dequeue();
            sqlite3_finalize(stmt);
        }         
    }
}

void FlightDatabase::beginTransaction() {
    char* errMsg = nullptr;
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errMsg);
}

// Success -> false
/*
bool FlightDatabase::executeTransaction() {
    // Begin transaction
    if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cout << "Failed to begin transaction: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    // Execute statements in 1 batch
    int transactions_sent = 0;
    while (!binded_stmt_queue.empty() && transactions_sent < TRANSACTION_MAX_BATCH_SIZE) {
        try{
            char* errMsg = nullptr;
            DbStatement lr = binded_stmt_queue.dequeue();
            sqlite3_stmt* stmt = lr.stmt;
            // Execute the statement
            int result = sqlite3_step(stmt);
            if (result != SQLITE_DONE) {
                std::cout << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
                //throw std::exception("SQL execution failed");
            }
            // Reset the statement
            if (sqlite3_reset(stmt) != SQLITE_OK) {
                std::cout << "Failed to reset statement: " << sqlite3_errmsg(db) << std::endl;
                //throw std::exception("SQL reset failed");
            }
            // Commit the transaction
            if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errMsg) != SQLITE_OK) {
                std::cout << "Failed to commit transaction: " << sqlite3_errmsg(db) << std::endl;
                //throw std::exception("SQL commit failed");
            }
            // Complete the transaction        
            // 1) Recycle the statement
            free_stmt_queues[lr.table]->enqueue(lr);
            // 2) Update the last transaction time
            last_trans = std::chrono::steady_clock::now();
            // 3) Update the transaction count
            transactions_sent++;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            db.rollbackTransaction();
            return true;
        }
    }
    return false;
}
*/

/*
bool FlightDatabase::executeTransaction() {
    if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cout << "Failed to begin transaction: " << sqlite3_errmsg(db) << std::endl;
        return true;
    }

// TODO: Add proccessing_vector for packets in a single transaction

    int transactions_sent = 0;
    while (!binded_stmt_queue.empty() && transactions_sent < TRANSACTION_MAX_BATCH_SIZE) {
        DbStatement lr = binded_stmt_queue.dequeue();
        sqlite3_stmt* stmt = lr.stmt;

        int result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            std::cout << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
            rollbackTransaction();
            return true;
        }

        if (sqlite3_reset(stmt) != SQLITE_OK) {
            std::cout << "Failed to reset statement: " << sqlite3_errmsg(db) << std::endl;
            rollbackTransaction();
            return true;
        }

        free_stmt_queues[static_cast<int>(lr.table)]->enqueue(stmt);
        last_trans = std::chrono::steady_clock::now();
        transactions_sent++;
    }

    if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cout << "Failed to commit transaction: " << sqlite3_errmsg(db) << std::endl;
        rollbackTransaction();
        return true;
    }

    return false;
}
*/

bool FlightDatabase::executeTransaction() {
    if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cout << "Failed to begin transaction: " << sqlite3_errmsg(db) << std::endl;
        return true;
    }

    int transactions_sent = 0;
    bool error_occurred = false;
    std::vector<DbStatement> processed_statements;

    while (!binded_stmt_queue.empty() && transactions_sent < TRANSACTION_MAX_BATCH_SIZE) {
        DbStatement lr = binded_stmt_queue.dequeue();
        sqlite3_stmt* stmt = lr.stmt;

        int result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            std::cout << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
            error_occurred = true;
            break;
        }

        if (sqlite3_reset(stmt) != SQLITE_OK) {
            std::cout << "Failed to reset statement: " << sqlite3_errmsg(db) << std::endl;
            error_occurred = true;
            break;
        }

        processed_statements.push_back(lr);
        last_trans = std::chrono::steady_clock::now();
        transactions_sent++;
    }

    if (error_occurred) {
        rollbackTransaction();
        // Re-enqueue processed statements
        for (auto it = processed_statements.rbegin(); it != processed_statements.rend(); ++it) {
            binded_stmt_queue.enqueue(*it);
        }
        return true;
    }

    if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cout << "Failed to commit transaction: " << sqlite3_errmsg(db) << std::endl;
        rollbackTransaction();
        // Re-enqueue processed statements
        for (auto it = processed_statements.rbegin(); it != processed_statements.rend(); ++it) {
            binded_stmt_queue.enqueue(*it);
        }
        return true;
    }

    // Transaction successful, free the processed statements
    for (const auto& lr : processed_statements) {
        free_stmt_queues[static_cast<int>(lr.table)]->enqueue(lr.stmt);
    }

    return false;
}


void FlightDatabase::rollbackTransaction() {
    char* errMsg = nullptr;
    sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, &errMsg);
}

/*
int64_t FlightDatabase::getCurrentTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
*/

// Success -> true    // Used to log by outsiders during operations

bool FlightDatabase::insertPlaneState(double pitch, double roll, double yaw) {
    if (free_plane_state_stmt_queue.empty()) {
        std::cout << "free_plane_state_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::PLANE_STATE, free_plane_state_stmt_queue.dequeue());
    
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, pitch);
    sqlite3_bind_double(lr.stmt, 3, roll);
    sqlite3_bind_double(lr.stmt, 4, yaw);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertServoData(int throttle, int elevator, int rudder, int left_aileron, int right_aileron) {
    if (free_servo_data_stmt_queue.empty()) {
        std::cout << "free_servo_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::SERVO_DATA, free_servo_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_int(lr.stmt, 2, throttle);
    sqlite3_bind_int(lr.stmt, 3, elevator);
    sqlite3_bind_int(lr.stmt, 4, rudder);
    sqlite3_bind_int(lr.stmt, 5, left_aileron);
    sqlite3_bind_int(lr.stmt, 6, right_aileron);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertGPSData(double latitude, double longitude, double altitude, double distance) {
    if (free_gps_data_stmt_queue.empty()) {
        std::cout << "free_gps_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::GPS_DATA, free_gps_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, latitude);
    sqlite3_bind_double(lr.stmt, 3, longitude);
    sqlite3_bind_double(lr.stmt, 4, altitude);
    sqlite3_bind_double(lr.stmt, 5, distance);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertGPSEnvData(double heading, double speed, int satellites, int signal_strength){
    if (free_gps_env_data_stmt_queue.empty()) {
        std::cout << "free_gps_env_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::GPS_ENV_DATA, free_gps_env_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, heading);
    sqlite3_bind_double(lr.stmt, 3, speed);
    sqlite3_bind_int(lr.stmt, 4, satellites);
    sqlite3_bind_int(lr.stmt, 5, signal_strength);
    binded_stmt_queue.enqueue(lr);
    return true;

}

bool FlightDatabase::insertAccelData(double accel_x, double accel_y, double accel_z) {
    if (free_accel_data_stmt_queue.empty()) {
        std::cout << "free_accel_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::ACCEL_DATA, free_accel_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, accel_x);
    sqlite3_bind_double(lr.stmt, 3, accel_y);
    sqlite3_bind_double(lr.stmt, 4, accel_z);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertGyroData(double gyro_x, double gyro_y, double gyro_z) {
    if (free_gyro_data_stmt_queue.empty()) {
        std::cout << "free_gyro_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::GYRO_DATA, free_gyro_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, gyro_x);
    sqlite3_bind_double(lr.stmt, 3, gyro_y);
    sqlite3_bind_double(lr.stmt, 4, gyro_z);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertMagData(double mag_x, double mag_y, double mag_z) {
    if (free_mag_data_stmt_queue.empty()) {
        std::cout << "free_mag_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::MAG_DATA, free_mag_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, mag_x);
    sqlite3_bind_double(lr.stmt, 3, mag_y);
    sqlite3_bind_double(lr.stmt, 4, mag_z);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertBaroData(double pressure, double temperature, double baro_altitude) {
    if (free_baro_data_stmt_queue.empty()) {
        std::cout << "free_baro_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::BARO_DATA, free_baro_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, pressure);
    sqlite3_bind_double(lr.stmt, 3, temperature);
    sqlite3_bind_double(lr.stmt, 4, baro_altitude);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertPIDData(PIDFeature feature, double Kp, double Ki, double Kd) {
    if (free_pid_data_stmt_queue.empty()) {
        std::cout << "free_pid_data_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::PID_DATA, free_pid_data_stmt_queue.dequeue());
    uint32_t timestamp = myTime::getTimestamp();
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_double(lr.stmt, 2, Kp);
    sqlite3_bind_double(lr.stmt, 3, Ki);
    sqlite3_bind_double(lr.stmt, 4, Kd);
    binded_stmt_queue.enqueue(lr);
    return true;
}

bool FlightDatabase::insertEventLog(EventType event_type, uint32_t timestamp, uint64_t data) {
    if (free_event_log_stmt_queue.empty()) {
        std::cout << "free_event_log_stmt_queue is empty" << std::endl;
        return false;
    }
    DbStatement lr(StatementType::EVENT_LOG, free_event_log_stmt_queue.dequeue());
    sqlite3_bind_int64(lr.stmt, 1, timestamp);
    sqlite3_bind_int(lr.stmt, 2, static_cast<int>(event_type));
    sqlite3_bind_int64(lr.stmt, 3, data);
    binded_stmt_queue.enqueue(lr);
    return true;
}