#pragma once
#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>

// Extras
    //const char* DB_SCHEMA_FILE = "atc_schema.sql";

// Constants
    const std::string DB_DIR = "FLIGHT_LOGS/";
    const std::string DB_DIR_STRING = "FLIGHT_LOGS/";
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
    struct DbStatement {
        StatementType table;    // Table/type
        sqlite3_stmt* stmt;     // Statement
        DbStatement(StatementType table, sqlite3_stmt* stmt) : table(table), stmt(stmt) {}
        DbStatement() {}
        ~DbStatement() {}
    }
    //template <class T> using DbStatement = std::pair<sqlite3_stmt*, T>;


// Tools
    //std::string getNextUniqueFilename();
    //std::string getFilename();

std::string getNextUniqueFilename() {
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
        std::cerr << "Unable to find an available filename in " << DB_DIR << std::endl;
    }
    return "";
}

std::string getFilename(){
    if (MULTI_FILE_MODE){
        return getNextUniqueFilename();
    } else {
        return DB_NAME;
    }
}


#endif // SQL_H