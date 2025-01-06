#pragma once
#include <sqlite3.h>

const int NUM_SQL_DB_TABLES = 10;

const char* db_table_names[] = {"atc_system", 
                            "system_status", 
                            "flight_status", 
                            "flight_vars", 
                            "servos", 
                            "gps_data", 
                            "imu_data", 
                            "baro_data", 
                            "pid_data",
                            "event_log"
                            };


const char* sql_atc_system = "INSERT INTO atc_system VALUES (?, ?, ?, ?)";
const char* sql_system_status = "INSERT INTO system_status VALUES (?, ?, ?, ?, ?, ?, ?)";
const char* sql_flight_status = "INSERT INTO flight_status VALUES (?, ?, ?, ?)";
const char* sql_flight_vars = "INSERT INTO flight_vars VALUES (?, ?, ?, ?, ?)";
const char* sql_servos = "INSERT INTO servos VALUES (?, ?, ?, ?, ?, ?)";
const char* sql_gps_data = "INSERT INTO gps_data VALUES (?, ?, ?, ?, ?, ?, ?)";
const char* sql_imu_data = "INSERT INTO imu_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
const char* sql_baro_data = "INSERT INTO baro_data VALUES (?, ?, ?, ?)";
const char* sql_pid_data = "INSERT INTO pid_data VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
const char* sql_event_log = "INSERT INTO event_log VALUES (?, ?, ?, ?)";
const char* sql[] = { sql_atc_system
                    ,sql_system_status
                    ,sql_flight_status
                    ,sql_flight_vars
                    ,sql_servos
                    ,sql_gps_data
                    ,sql_imu_data
                    ,sql_baro_data
                    ,sql_pid_data
                    ,sql_event_log
                    };

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





const char* db_create_table_transactions[] = {
        // ATC System
        "CREATE TABLE atc_system("
        "timestamp INTEGER PRIMARY KEY,"
        "ctlr_paired BOOLEAN,"
        "rf_rx_active BOOLEAN,"
        "rf_tx_active BOOLEAN"
        ");",

        // System Status
        /*
        "CREATE TABLE system_status("
        "timestamp INTEGER PRIMARY KEY,"
        "control_mode INTEGER,"
        "paired BOOLEAN,"
        "throttle_lock BOOLEAN,"
        "holding_pattern BOOLEAN,"
        "taxi_only BOOLEAN,"
        "gps_active BOOLEAN"
        ");",
        */


        // System Status
        "CREATE TABLE system_status("
        "timestamp INTEGER PRIMARY KEY,"
        "control_mode INTEGER,"
        "paired BOOLEAN,"
        "throttle_lock BOOLEAN,"
        "holding_pattern BOOLEAN,"
        "taxi_only BOOLEAN,"
        "gps_active BOOLEAN"
        ");",

        // Flight Status
        "CREATE TABLE flight_status("
        "timestamp INTEGER PRIMARY KEY,"
        "battery_level REAL,"
        "signal_strength REAL,"
        "flying BOOLEAN"
        ");",

        // Flight Vars
        "CREATE TABLE flight_vars ("
        "timestamp INTEGER PRIMARY KEY,"
        "pitch REAL,"
        "roll REAL,"
        "yaw REAL,"
        "distance REAL"
        ");",

        // Servos
        "CREATE TABLE servos ("
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
        "speed REAL,"
        "satellites INTEGER,"
        "signal_strength INTEGER"
        ");",

        // IMU Data
        "CREATE TABLE imu_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "accel_x REAL,"
        "accel_y REAL,"
        "accel_z REAL,"
        "gyro_x REAL,"
        "gyro_y REAL,"
        "gyro_z REAL,"
        "mag_x REAL,"
        "mag_y REAL,"
        "mag_z REAL"
        ");",

        // Baro Data
        "CREATE TABLE baro_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "pressure REAL,"
        "temperature REAL,"
        "calculated_altitude REAL"
        ");",

        // PID Data
        "CREATE TABLE pid_data ("
        "timestamp INTEGER PRIMARY KEY,"
        "roll_p REAL,"
        "roll_i REAL,"
        "roll_d REAL,"
        "yaw_p REAL,"
        "yaw_i REAL,"
        "yaw_d REAL,"
        "pitch_p REAL,"
        "pitch_i REAL,"
        "pitch_d REAL"
        ");",


        // Event Log
        "CREATE TABLE event_log ("
        "timestamp INTEGER PRIMARY KEY,"
        "event_type INTEGER,"
        "event_code INTEGER,"
        "event_data STRING"
        ");",

    };


/*

const char* db_create_table_transactions[] = {

// ATC System
    "CREATE TABLE atc_system(
        timestamp INTEGER PRIMARY KEY,
        ctlr_paired BOOlEAN,
        rf_rx_active BOOlEAN,
        rf_tx_active BOOlEAN
    );",

// System Status
    "CREATE TABLE system_status(
        timestamp INTEGER PRIMARY KEY,
        control_mode INTEGER,
        paired BOOlEAN,
        throttle_lock BOOlEAN,
        holding_pattern BOOlEAN,
        taxi_only BOOlEAN,
        gps_active BOOlEAN
    );",

// Flight Status
    "CREATE TABLE flight_status(
        timestamp INTEGER PRIMARY KEY,
        battery_level REAL,
        signal_strength REAL,
    );",

// Flight Vars
    "CREATE TABLE flight_vars (
        timestamp INTEGER PRIMARY KEY,
        pitch REAL,
        roll REAL,
        yaw REAL,
        distance REAL
    );
    ",

// Servos
    "CREATE TABLE servos (
        timestamp INTEGER PRIMARY KEY,
        throttle INTEGER,
        elevator INTEGER,
        rudder INTEGER,
        left_aileron INTEGER,
        right_aileron INTEGER
    );",

// GPS Data
    "CREATE TABLE gps_data (
        timestamp INTEGER PRIMARY KEY,
        latitude REAL,
        longitude REAL,
        altitude REAL,
        speed REAL,
        satellites INTEGER,
        signal_strength INTEGER
    );
    ",

// IMU Data
    "CREATE TABLE imu_data (
        timestamp INTEGER PRIMARY KEY,
        accel_x REAL,
        accel_y REAL,
        accel_z REAL,
        gyro_x REAL,
        gyro_y REAL,
        gyro_z REAL,
        mag_x REAL,
        mag_y REAL,
        mag_z REAL
    );",  

// Baro Data
    "CREATE TABLE baro_data (
        timestamp INTEGER PRIMARY KEY,
        pressure REAL,
        temperature REAL
    );",

// PID Data
    "CREATE TABLE pid_data (
        timestamp INTEGER PRIMARY KEY,
        roll_p REAL,
        roll_i REAL,
        roll_d REAL,
        yaw_p REAL,
        yaw_i REAL,
        yaw_d REAL,
        pitch_p REAL,
        pitch_i REAL,
        pitch_d REAL
    );"

};

*/

//int num_tables = sizeof(db_create_table_transactions) / sizeof(db_create_table_transactions[0]);


