#ifndef FLIGHTDATABASE_H
#define FLIGHTDATABASE_H
#pragma once

#include <vector>
#include <chrono>
#include "SQL.h"
#include "ThreadSafeQueue.h"
#include "EventTypes.h"
#include "PIDFeature.h"
#include <string>
#include <thread>

class FlightDatabase {
private:

    std::chrono::steady_clock::time_point last_trans;
    sqlite3* db;


    // TODO: Add lock to prevent new statements from being added
    ThreadSafeQueue<DbStatement> binded_stmt_queue{50}; //= ThreadSafeQueue<DbStatement>(50);    // SQL statement queue
    
    // Queues for free statements, for re-use, for each table
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


    ThreadSafeQueue<sqlite3_stmt*>* free_stmt_queues[10];    // TODO: replace 10 with NUM_SQL_DB_TABLES
    
    bool setSchema();
    void createStatements();
    void finalizeStatements();
    void beginTransaction();
    void rollbackTransaction();
    //int64_t getCurrentTimestamp();
    std::thread DB_thread;

public:

    void startDBLoop();
    void stopDBLoop();

    bool saveDB();

    // Success -> false
    bool executeTransaction();
    inline void DB_loop();
    FlightDatabase(std::string dbname);
    ~FlightDatabase();

    // Success -> true
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