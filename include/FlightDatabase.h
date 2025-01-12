#ifndef FLIGHTDATABASE_H
#define FLIGHTDATABASE_H

#pragma once

#include <vector>
#include <chrono>
//#include "Schema.h"
//#include "Schema1.h"
#include "SQL.h"
#include "ThreadSafeQueue.h"
#include "EventTypes.h"
#include "PIDFeature.h"
#include <string>
//#include <exception>
//#include <iostream>

#include <thread>

class FlightDatabase {
private:
//public:
    //auto last_trans; = std::chrono::steady_clock::now();
    //uint64_t last_trans;
    std::chrono::steady_clock::time_point last_trans;
    sqlite3* db;


    //std::vector<DbStatement> binded_stmt_queue;
    // Queue for binded statements (all tables) to be executed

    //ThreadSafeQueue<DbStatement> binded_stmt_queue = ThreadSafeQueue<DbStatement>(50);    // SQL statement queue
    ThreadSafeQueue<DbStatement> binded_stmt_queue{50}; //= ThreadSafeQueue<DbStatement>(50);    // SQL statement queue

/*
    Queues for free statements, for re-use, for each table
*/
    // Queue for each table
    //ThreadSafeQueue<sqlite3_stmt*> free_atc_system_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_system_status_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_flight_status_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_flight_vars_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_servos_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_gps_data_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_imu_data_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_baro_data_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_pid_data_stmt_queue;
    //ThreadSafeQueue<sqlite3_stmt*> free_event_log_stmt_queue;


    ThreadSafeQueue<sqlite3_stmt*> free_plane_state_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_servo_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_gps_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_gps_env_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_accel_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_gyro_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_mag_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_baro_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_pid_data_stmt_queue{30};
    ThreadSafeQueue<sqlite3_stmt*> free_event_log_stmt_queue{30};
    // Vector of queue references
    //std::vector<<ThreadSafeQueue<sqlite3_stmt*>&> free_stmt_queues;
    //ThreadSafeQueue<sqlite3_stmt*>* free_stmt_queues[NUM_SQL_DB_TABLES];

    ThreadSafeQueue<sqlite3_stmt*>* free_stmt_queues[10];    // TODO: replace 10 with NUM_SQL_DB_TABLES
    //std::vector<std::reference_wrapper<ThreadSafeQueue<sqlite3_stmt*>>> free_stmt_queues;
    
    bool setSchema();
    void createStatements();
    void finalizeStatements();
    void beginTransaction();
    void rollbackTransaction();
    //int64_t getCurrentTimestamp();
    //bool db_loop_active = false;

    std::thread DB_thread;
    //bool DB_loop_active = false;

    //std::thread dbThread(&FlightDatabase::DB_loop, DB);

public:

    void startDBLoop();
    void stopDBLoop();

    bool saveDB();

    // Success -> false
    bool executeTransaction();
    inline void DB_loop();
    //FlightDatabase(const char* dbname);
    FlightDatabase(std::string dbname);
    ~FlightDatabase();

    // Success -> true

    //void enableDBLoop() { db_loop_active = true; }
    //void disableDBLoop() { db_loop_active = false; }

    bool insertPlaneState(double pitch, double roll, double yaw);
    bool insertServoData(int throttle, int elevator, int rudder, int left_aileron, int right_aileron);
    bool insertGPSData(double latitude, double longitude, double altitude, double speed);
    bool insertGPSEnvData(double heading, double speed, int satellites, int signal_strength);
    bool insertAccelData(double accel_x, double accel_y, double accel_z);
    bool insertGyroData(double gyro_x, double gyro_y, double gyro_z);
    bool insertMagData(double mag_x, double mag_y, double mag_z);
    bool insertBaroData(double pressure, double temperature, double baro_altitude);

    bool insertPIDData(PIDFeature feature, double Kp, double Ki, double Kd);
    bool insertEventLog(EventType event_type, uint32_t timestamp, uint64_t data);

};


#endif // FLIGHTDATABASE_H