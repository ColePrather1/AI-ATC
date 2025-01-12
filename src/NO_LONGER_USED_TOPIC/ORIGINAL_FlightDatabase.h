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
    //inline bool insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active);
    //inline bool insertSystemStatus(int control_mode, bool paired, bool throttle_lock,bool holding_pattern, bool taxi_only, bool gps_active);
    //inline bool insertFlightStatus(double battery_level, double signal_strength, bool flying);
    //inline bool insertFlightVars(double pitch, double roll, double yaw, double distance);
    //inline bool insertServos(int throttle, int elevator, int rudder, int left_aileron, int right_aileron);
    //inline bool insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength);
    //inline bool insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z);
    //inline bool insertBaroData(double pressure, double temperature, double calculated_altitude);
    //inline bool insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d);
    //inline bool insertEventLog(int event_type, int event_code, std::string event_description);


    //bool insertPlaneState(uint32_t pitch, uint32_t roll, uint32_t yaw);
    //bool insertServos(uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    //bool insertGPSData(uint32_t latitude, uint32_t longitude, uint16_t altitude, uint16_t distance_meters);
    //bool insertGPSEnvData(uint16_t heading, uint16_t speed, uint8_t satellites, int8_t signal_strength);
    //bool insertAccelData(uint32_t accel_x, uint32_t accel_y, uint32_t accel_z);
    //bool insertGyroData(uint32_t gyro_x, uint32_t gyro_y, uint32_t gyro_z);
    //bool insertMagData(uint32_t mag_x, uint32_t mag_y, uint32_t mag_z);
    //bool insertBaroData(uint32_t pressure, uint32_t temperature, uint32_t baro_altitude);
    //bool insertPIDData(PIDFeatures feature, double p, double i, double d);
    //bool insertEventLog(EventType event_type); 
    //bool insertEventLog(EventType event_type, uint8_t data);    // Metadata = agreed, future use
    //bool insertEventLog(EventType event_type, uint32_t timestamp); 

    bool insertPlaneState(double pitch, double roll, double yaw);
    bool insertServos(uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    bool insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength);
    bool insertGPSEnvData(double heading, double speed, int satellites, int signal_strength);
    bool insertAccelData(float accel_x, float accel_y, float accel_z);
    bool insertGyroData(float gyro_x, float gyro_y, float gyro_z);
    bool insertMagData(float mag_x, float mag_y, float mag_z);
    bool insertBaroData(float pressure, float temperature, float baro_altitude);
    bool insertPIDData(PIDFeatures feature, double Kp, double Ki, double Kd);
    bool insertEventLog(EventType event_type, uint32_t timestamp, uint64_t data);
    //bool insertEventLog(EventType event_type); 
    //bool insertEventLog(EventType event_type, uint64_t data);
    //bool insertEventLog(EventType event_type, uint32_t timestamp);

};


#endif // FLIGHTDATABASE_H