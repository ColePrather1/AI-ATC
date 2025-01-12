#ifndef SQL_H
#define SQL_H
#pragma once


#include <sqlite3.h>
//#include <iostream>
#include <string>
#include <filesystem>
#include <iostream>

//#define MULTI_FILE_MODE false


// Extras
    //const char* DB_SCHEMA_FILE = "atc_schema.sql";

// Constants
    /*
    extern const std::string DB_DIR;
    extern const std::string DB_DIR_STRING;
    extern const std::string DB_NAME_BASE;
    extern const std::string DB_FILE_TYPE;
    extern const int DB_MAX_FILES;

    extern const int TRANSACTION_MAX_DELAY_MS ;
    extern const int TRANSACTION_MIN_BATCH_SIZE ;
    extern const int TRANSACTION_MAX_BATCH_SIZE ;
    extern const int NUM_SQL_BINDED_STATEMENTS ;         // TEST : check during testing
    extern const int NUM_SQL_UNBINDED_STATEMENTS_EACH_TABLE ;         // TEST : check during testing

    const bool MULTI_FILE_MODE;
    const std::string DB_NAME.db;
    */

    
    //constexpr std::string DB_DIR = "FLIGHT_LOGS/";
    //constexpr std::string DB_DIR_STRING = "FLIGHT_LOGS/";
    const std::string DB_DIR_STRING = "";
    const std::string DB_DIR = "";
    const std::string DB_NAME_BASE = "flight_";
    const std::string DB_FILE_TYPE = ".db";
    const int DB_MAX_FILES = 25;
    const int TRANSACTION_MAX_DELAY_MS = 1000;
    const int TRANSACTION_MIN_BATCH_SIZE = 10;
    const int TRANSACTION_MAX_BATCH_SIZE = 15;
    const int NUM_SQL_BINDED_STATEMENTS = 100;         // TEST : check during testing
    const int NUM_SQL_UNBINDED_STATEMENTS_EACH_TABLE = 10;         // TEST : check during testing
    const bool MULTI_FILE_MODE = false;
    const std::string DB_NAME = DB_DIR_STRING + "dev.db";
  

// DB Statement Package
    /*
    enum class StatementType {
        ATC_SYSTEM,
        SYSTEM_STATUS,
        FLIGHT_STATUS,
        FLIGHT_VARS,
        SERVOS,
        GPS_DATA,
        IMU_DATA,
        BARO_DATA,
        PID_DATA,
        EVENT_LOG
    };
    */

    enum class StatementType : int {
        PLANE_STATE,
        SERVO_DATA,
        GPS_DATA,
        GPS_ENV_DATA,
        ACCEL_DATA,
        GYRO_DATA,
        MAG_DATA,
        BARO_DATA,
        PID_DATA,
        EVENT_LOG
    };

    struct DbStatement {
        StatementType table;    // Table/type
        sqlite3_stmt* stmt;     // Statement
        DbStatement(StatementType table, sqlite3_stmt* stmt) : table(table), stmt(stmt) {}
        DbStatement() {}
        ~DbStatement() {}
    };
    //template <class T> using DbStatement = std::pair<sqlite3_stmt*, T>;


// Tools
    //std::string getNextUniqueFilename();
    //std::string getFilename();

inline std::string getNextUniqueFilename() {
    int suffix = 0;
    std::string filename = "";
    
    while (true && suffix < DB_MAX_FILES) {
        filename = DB_DIR + DB_NAME_BASE + std::to_string(suffix) + DB_FILE_TYPE;
        
        if (!std::filesystem::exists(filename)) {
            return filename;
            std::cout << filename << std::endl;
        }
        suffix++;
    }
    if (filename == "") {
        std::cout << "Unable to find an available filename in " << DB_DIR << std::endl;
    }
    return "";
}

inline std::string getFilename(){
    if (MULTI_FILE_MODE){
        return getNextUniqueFilename();
    } else {
        return DB_NAME;
    }
}




#endif // SQL_H