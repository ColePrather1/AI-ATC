#ifndef FLIGHTDATABASE_H
#define FLIGHTDATABASE_H

#pragma once

#include <vector>
#include <chrono>
#include "Schema.h"
//#include "Schema1.h"
#include "SQL.h"
#include "ThreadSafeQueue.h"
//#include <exception>
//#include <iostream>

class FlightDatabase {
private:
//public:
    //auto last_trans; = std::chrono::steady_clock::now();
    //uint64_t last_trans;
    std::chrono::steady_clock::time_point last_trans;
    sqlite3* db;

    // Queue for binded statements (all tables) to be executed
    ThreadSafeQueue<DbStatement> binded_stmt_queue;    // SQL statement queue

/*
    Queues for free statements, for re-use, for each table
*/
    // Queue for each table
    ThreadSafeQueue<sqlite3_stmt*> free_atc_system_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_system_status_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_flight_status_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_flight_vars_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_servos_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_gps_data_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_imu_data_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_baro_data_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_pid_data_stmt_queue;
    ThreadSafeQueue<sqlite3_stmt*> free_event_log_stmt_queue;
    // Vector of queue references
    std::vector<std::reference_wrapper<ThreadSafeQueue<sqlite3_stmt*>>> free_stmt_queues;
    
    bool setSchema();
    void createStatements();
    void finalizeStatements();
    void beginTransaction();
    void rollbackTransaction();
    int64_t getCurrentTimestamp();

public:

    // Success -> false
    bool executeTransaction();
    inline void DB_loop();
    FlightDatabase(const char* dbname);
    ~FlightDatabase();

    // Success -> true
    inline bool insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active);
    inline bool insertSystemStatus(int control_mode, bool paired, bool throttle_lock,bool holding_pattern, bool taxi_only, bool gps_active);
    inline bool insertFlightStatus(double battery_level, double signal_strength, bool flying);
    inline bool insertFlightVars(double pitch, double roll, double yaw, double distance);
    inline bool insertServos(int throttle, int elevator, int rudder, int left_aileron, int right_aileron);
    inline bool insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength);
    inline bool insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z);
    inline bool insertBaroData(double pressure, double temperature, double calculated_altitude);
    inline bool insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d);
    inline bool insertEventLog(int event_type, int event_code, std::string event_description);

};


#endif // FLIGHTDATABASE_H