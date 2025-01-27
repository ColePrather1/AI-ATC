#ifndef SCHEMA_H
#define SCHEMA_H
#pragma once
#include <sqlite3.h>

const int NUM_SQL_DB_TABLES = 10;

const char* db_table_names[] = {
                            //"atc_system", 
                            //"system_status", 
                            //"flight_status", 
                            //"flight_vars", 
                            //"imu_data", 
                            "plane_state",
                            "servo_data", 
                            "gps_data", 
                            "gps_env_data",
                            "accel_data",
                            "gyro_data",
                            "mag_data",
                            "baro_data", 
                            "pid_data",
                            "event_log"
                            };




const char* sql_create_statements[NUM_SQL_DB_TABLES] = { 
    "INSERT INTO plane_state VALUES (?, ?, ?, ?)",
    "INSERT INTO servo_data VALUES (?, ?, ?, ?, ?, ?)",
    "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO gps_env_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO accel_data VALUES (?, ?, ?, ?)",
    "INSERT INTO gyro_data VALUES (?, ?, ?, ?)",
    "INSERT INTO mag_data VALUES (?, ?, ?, ?)",
    "INSERT INTO baro_data VALUES (?, ?, ?, ?)",
    "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO event_log VALUES (?, ?, ?)"
};                

const char* db_create_table_transactions[] = {

        // Plane State
        "CREATE TABLE plane_state ("
        "timestamp INTEGER PRIMARY KEY,"
        "pitch REAL,"
        "roll REAL,"
        "yaw REAL"
        ");",       

        // Servos
        "CREATE TABLE servo_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "throttle INTEGER,"
        "elevator INTEGER,"
        "rudder INTEGER,"
        "left_aileron INTEGER,"
        "right_aileron INTEGER"
        ");",

        // GPS Data
        "CREATE TABLE gps_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "latitude REAL,"
        "longitude REAL,"
        "altitude REAL,"
        "distance REAL"
        ");",

        // GPS Environment Data
        "CREATE TABLE gps_env_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "heading REAL,"
        "speed REAL,"
        "satellites INTEGER,"
        "signal_strength INTEGER"
        ");",

        // Accelerometer Data
        "CREATE TABLE accel_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "accel_x REAL,"
        "accel_y REAL,"
        "accel_z REAL"
        ");",

        // Gyroscope Data
        "CREATE TABLE gyro_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "gyro_x REAL,"
        "gyro_y REAL,"
        "gyro_z REAL"
        ");",

        // Magnetometer Data
        "CREATE TABLE mag_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "mag_x REAL,"
        "mag_y REAL,"
        "mag_z REAL"
        ");",

        // Barometer Data
        "CREATE TABLE baro_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "pressure REAL,"
        "temperature REAL,"
        "calculated_altitude REAL"
        ");",

        // PID Data
        "CREATE TABLE pid_data ("
        "timestamp INTEGER,"
        "PIDFeature INTEGER,"
        "p REAL,"
        "i REAL,"
        "d REAL,"
        "PRIMARY KEY (timestamp, PIDFeature)"
        ");",


        // Event Log
        "CREATE TABLE event_log ("
        "timestamp INTEGER,"
        "event_type INTEGER,"
        "event_data INTEGER,"
        "PRIMARY KEY (timestamp, event_type)"
        ");",

};

#endif // SCHEMA_H