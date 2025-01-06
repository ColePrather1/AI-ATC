#pragma once
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "Schema.h"
#include "SQL.h"

#include <filesystem>





class AirplaneDatabase {
private:
    sqlite3* db;
    sqlite3_stmt* stmt_atc_system;
    sqlite3_stmt* stmt_system_status;
    sqlite3_stmt* stmt_flight_status;
    sqlite3_stmt* stmt_flight_vars;
    sqlite3_stmt* stmt_servos;
    sqlite3_stmt* stmt_gps_data;
    sqlite3_stmt* stmt_imu_data;
    sqlite3_stmt* stmt_baro_data;
    sqlite3_stmt* stmt_pid_data;

public:
    AirplaneDatabase(const char* dbname) {
        if (sqlite3_open(dbname, &db) != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }




/*
    char* errMsg = nullptr;
    int rc;

    // Read SQL file
    std::ifstream sqlFile("atc_schema.sql");
    std::string sql((std::istreambuf_iterator<char>(sqlFile)),
                     std::istreambuf_iterator<char>());
    // Execute SQL   
    std::string schema = getSchema();
    rc = sqlite3_exec(db, schema.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    } else {
        std::cout << "Database schema created successfully" << std::endl;
        return 0;
    }
*/


        if (setSchema() != SQLITE_OK){
            std::cerr << "Can't define database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        prepareStatements();
    }

    ~AirplaneDatabase() {
        finalizeStatements();
        sqlite3_close(db);
    }

    bool setSchema() {    
        char* errMsg = nullptr;

        for (int i = 0; i < num_tables; i++) {
            int rc = sqlite3_exec(db, db_create_table_transactions[i], nullptr, nullptr, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                return rc;
            }
        }

        std::cout << "Database schema created successfully" << std::endl;
        return SQLITE_OK;

    }


    void prepareStatements() {
        const char* sql_atc_system = "INSERT INTO atc_system VALUES (?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_atc_system, -1, &stmt_atc_system, NULL);

        const char* sql_system_status = "INSERT INTO system_status VALUES (?, ?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_system_status, -1, &stmt_system_status, NULL);

        const char* sql_flight_status = "INSERT INTO flight_status VALUES (?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_flight_status, -1, &stmt_flight_status, NULL);

        const char* sql_flight_vars = "INSERT INTO flight_vars VALUES (?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_flight_vars, -1, &stmt_flight_vars, NULL);

        const char* sql_servos = "INSERT INTO servos VALUES (?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_servos, -1, &stmt_servos, NULL);

        const char* sql_gps_data = "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_gps_data, -1, &stmt_gps_data, NULL);

        const char* sql_imu_data = "INSERT INTO imu_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_imu_data, -1, &stmt_imu_data, NULL);

        const char* sql_baro_data = "INSERT INTO baro_data VALUES (?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_baro_data, -1, &stmt_baro_data, NULL);

        const char* sql_pid_data = "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        sqlite3_prepare_v2(db, sql_pid_data, -1, &stmt_pid_data, NULL);
    }

    void finalizeStatements() {
        sqlite3_finalize(stmt_atc_system);
        sqlite3_finalize(stmt_system_status);
        sqlite3_finalize(stmt_flight_status);
        sqlite3_finalize(stmt_flight_vars);
        sqlite3_finalize(stmt_servos);
        sqlite3_finalize(stmt_gps_data);
        sqlite3_finalize(stmt_imu_data);
        sqlite3_finalize(stmt_baro_data);
        sqlite3_finalize(stmt_pid_data);
    }

    void beginTransaction() {
        char* errMsg = nullptr;
        sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errMsg);
    }

    /*
    void endTransaction() {
        char* errMsg = nullptr;
        sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errMsg);
    }
    */

    void rollbackTransaction() {
        char* errMsg = nullptr;
        sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, &errMsg);
    }

    void commitTransaction() {
        char* errMsg = nullptr;
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errMsg);
    }


    int64_t getCurrentTimestamp() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    void insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_atc_system, 1, timestamp);
        sqlite3_bind_int(stmt_atc_system, 2, ctlr_paired);
        sqlite3_bind_int(stmt_atc_system, 3, rf_rx_active);
        sqlite3_bind_int(stmt_atc_system, 4, rf_tx_active);
        sqlite3_step(stmt_atc_system);
        sqlite3_reset(stmt_atc_system);
    }

    void insertSystemStatus(int control_mode, bool paired, bool throttle_lock, 
                            bool holding_pattern, bool taxi_only, bool gps_active) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_system_status, 1, timestamp);
        sqlite3_bind_int(stmt_system_status, 2, control_mode);
        sqlite3_bind_int(stmt_system_status, 3, paired);
        sqlite3_bind_int(stmt_system_status, 4, throttle_lock);
        sqlite3_bind_int(stmt_system_status, 5, holding_pattern);
        sqlite3_bind_int(stmt_system_status, 6, taxi_only);
        sqlite3_bind_int(stmt_system_status, 7, gps_active);
        sqlite3_step(stmt_system_status);
        sqlite3_reset(stmt_system_status);
    }

    void insertFlightStatus(double battery_level, double signal_strength, bool flying) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_flight_status, 1, timestamp);
        sqlite3_bind_double(stmt_flight_status, 2, battery_level);
        sqlite3_bind_double(stmt_flight_status, 3, signal_strength);
        sqlite3_bind_int(stmt_flight_status, 4, flying);
        sqlite3_step(stmt_flight_status);
        sqlite3_reset(stmt_flight_status);
    }

    void insertFlightVars(double pitch, double roll, double yaw, double distance) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_flight_vars, 1, timestamp);
        sqlite3_bind_double(stmt_flight_vars, 2, pitch);
        sqlite3_bind_double(stmt_flight_vars, 3, roll);
        sqlite3_bind_double(stmt_flight_vars, 4, yaw);
        sqlite3_bind_double(stmt_flight_vars, 5, distance);
        sqlite3_step(stmt_flight_vars);
        sqlite3_reset(stmt_flight_vars);
    }

    void insertServos(int throttle, int elevator, int rudder, int left_aileron, int right_aileron) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_servos, 1, timestamp);
        sqlite3_bind_int(stmt_servos, 2, throttle);
        sqlite3_bind_int(stmt_servos, 3, elevator);
        sqlite3_bind_int(stmt_servos, 4, rudder);
        sqlite3_bind_int(stmt_servos, 5, left_aileron);
        sqlite3_bind_int(stmt_servos, 6, right_aileron);
        sqlite3_step(stmt_servos);
        sqlite3_reset(stmt_servos);
    }

    void insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_gps_data, 1, timestamp);
        sqlite3_bind_double(stmt_gps_data, 2, latitude);
        sqlite3_bind_double(stmt_gps_data, 3, longitude);
        sqlite3_bind_double(stmt_gps_data, 4, altitude);
        sqlite3_bind_double(stmt_gps_data, 5, speed);
        sqlite3_bind_int(stmt_gps_data, 6, satellites);
        sqlite3_bind_int(stmt_gps_data, 7, signal_strength);
        sqlite3_step(stmt_gps_data);
        sqlite3_reset(stmt_gps_data);
    }

    void insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_imu_data, 1, timestamp);
        sqlite3_bind_double(stmt_imu_data, 2, accel_x);
        sqlite3_bind_double(stmt_imu_data, 3, accel_y);
        sqlite3_bind_double(stmt_imu_data, 4, accel_z);
        sqlite3_bind_double(stmt_imu_data, 5, gyro_x);
        sqlite3_bind_double(stmt_imu_data, 6, gyro_y);
        sqlite3_bind_double(stmt_imu_data, 7, gyro_z);
        sqlite3_bind_double(stmt_imu_data, 8, mag_x);
        sqlite3_bind_double(stmt_imu_data, 9, mag_y);
        sqlite3_bind_double(stmt_imu_data, 10, mag_z);
        sqlite3_step(stmt_imu_data);
        sqlite3_reset(stmt_imu_data);
    }

    void insertBaroData(double pressure, double temperature, double calculated_altitude) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_baro_data, 1, timestamp);
        sqlite3_bind_double(stmt_baro_data, 2, pressure);
        sqlite3_bind_double(stmt_baro_data, 3, temperature);
        sqlite3_bind_double(stmt_baro_data, 4, calculated_altitude);
        sqlite3_step(stmt_baro_data);
        sqlite3_reset(stmt_baro_data);
    }

    void insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d) {
        int64_t timestamp = getCurrentTimestamp();
        sqlite3_bind_int64(stmt_pid_data, 1, timestamp);
        sqlite3_bind_double(stmt_pid_data, 2, roll_p);
        sqlite3_bind_double(stmt_pid_data, 3, roll_i);
        sqlite3_bind_double(stmt_pid_data, 4, roll_d);
        sqlite3_bind_double(stmt_pid_data, 5, yaw_p);
        sqlite3_bind_double(stmt_pid_data, 6, yaw_i);
        sqlite3_bind_double(stmt_pid_data, 7, yaw_d);
        sqlite3_bind_double(stmt_pid_data, 8, pitch_p);
        sqlite3_bind_double(stmt_pid_data, 9, pitch_i);
        sqlite3_bind_double(stmt_pid_data, 10, pitch_d);
        sqlite3_step(stmt_pid_data);
        sqlite3_reset(stmt_pid_data);
    }




    /*
    void insertBulkData(const std::vector<double>& data) {
        beginTransaction();
        
        insertFlightVars(data[0], data[1], data[2], data[3]);
        insertServos(data[4], data[5], data[6], data[7], data[8]);
        insertGPSData(data[9], data[10], data[11], data[12], data[13], data[14]);
        insertIMUData(data[15], data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23]);
        insertBaroData(data[24], data[25], data[26]);
        insertPIDData(data[27], data[28], data[29], data[30], data[31], data[32], data[33], data[34], data[35]);
        
        endTransaction();
    }
    */



};


