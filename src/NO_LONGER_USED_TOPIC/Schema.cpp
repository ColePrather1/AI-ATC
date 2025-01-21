#ifndef SCHEMA_H
#define SCHEMA_H
#pragma once
#include <sqlite3.h>

NUM_SQL_DB_TABLES = 10;

//extern const char*
db_table_names = {
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


//const char* sql_atc_system = "INSERT INTO atc_system VALUES (?, ?, ?, ?)";
//const char* sql_system_status = "INSERT INTO system_status VALUES (?, ?, ?, ?, ?, ?, ?)";
//const char* sql_flight_status = "INSERT INTO flight_status VALUES (?, ?, ?, ?)";
//const char* sql_flight_vars = "INSERT INTO flight_vars VALUES (?, ?, ?, ?, ?)";
/*
const char* sql_plane_state = "INSERT INTO plane_state VALUES (?, ?, ?, ?)";
const char* sql_servo_data = "INSERT INTO servo_data VALUES (?, ?, ?, ?, ?, ?)";
const char* sql_gps_data = "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?)";
const char* sql_gps_env_data = "INSERT INTO gps_env_data VALUES (?, ?, ?, ?, ?)";
const char* sql_accel_data = "INSERT INTO accel_data VALUES (?, ?, ?, ?)";
const char* sql_gyro_data = "INSERT INTO gyro_data VALUES (?, ?, ?, ?)";
const char* sql_mag_data = "INSERT INTO mag_data VALUES (?, ?, ?, ?)";
const char* sql_baro_data = "INSERT INTO baro_data VALUES (?, ?, ?, ?)";
const char* sql_pid_data = "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?)";
const char* sql_event_log = "INSERT INTO event_log VALUES (?, ?, ?)";
*/
//const char* sql_create_statements[NUM_SQL_DB_TABLES];

//sql_create_statements[0] = &sql_plane_state;
//sql_create_statements[1] = &sql_servo_data;
//sql_create_statements[2] = &sql_gps_data;
//sql_create_statements[3] = &sql_gps_env_data;
//sql_create_statements[4] = &sql_accel_data;
//sql_create_statements[5] = &sql_gyro_data;
//sql_create_statements[6] = &sql_mag_data;
//sql_create_statements[7] = &sql_baro_data;
//sql_create_statements[8] = &sql_pid_data;
//sql_create_statements[9] = &sql_event_log;

extern const char*
//sql_create_statements[NUM_SQL_DB_TABLES] = { 
    "INSERT INTO plane_state VALUES (?, ?, ?, ?)"
    "INSERT INTO servo_data VALUES (?, ?, ?, ?, ?, ?)",
    "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO gps_env_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO accel_data VALUES (?, ?, ?, ?)",
    "INSERT INTO gyro_data VALUES (?, ?, ?, ?)",
    "INSERT INTO mag_data VALUES (?, ?, ?, ?)",
    "INSERT INTO baro_data VALUES (?, ?, ?, ?)",
    "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?)",
    "INSERT INTO event_log VALUES (?, ?, ?)",
};

/*
const char* sql_create_statements[] = { 
                    &sql_plane_state
                    ,&sql_servo_data
                    ,&sql_gps_data
                    ,&sql_gps_env_data
                    ,&sql_accel_data
                    ,&sql_gyro_data
                    ,&sql_mag_data
                    ,&sql_baro_data
                    ,&sql_pid_data
                    ,&sql_event_log
                    };
*/                    


/*
const char* sql_atc_system = "INSERT INTO atc_system VALUES (?, ?, ?, ?)";
const char* sql_system_status = "INSERT INTO system_status VALUES (?, ?, ?, ?, ?, ?, ?)";
const char* sql_flight_status = "INSERT INTO flight_status VALUES (?, ?, ?, ?)";
const char* sql_flight_vars = "INSERT INTO flight_vars VALUES (?, ?, ?, ?, ?)";
const char* sql_servos = "INSERT INTO servos VALUES (?, ?, ?, ?, ?, ?)";
const char* sql_gps_data = "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?, ?, ?)";
const char* sql_imu_data = "INSERT INTO imu_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
const char* sql_baro_data = "INSERT INTO baro_data VALUES (?, ?, ?, ?)";
const char* sql_pid_data = "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
*/





//extern const char* 
db_create_table_transactions[] = {
        

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
        "distance REAL,"
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
        "accel_z REAL,"
        ");",

        // Gyroscope Data
        "CREATE TABLE gyro_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "gyro_x REAL,"
        "gyro_y REAL,"
        "gyro_z REAL,"
        ");",

        // Magnetometer Data
        "CREATE TABLE mag_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "mag_x REAL,"
        "mag_y REAL,"
        "mag_z REAL,"
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
