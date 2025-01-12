#include "SQL.h"

#include <string>
#include <filesystem>
#include <iostream>


// Constants
     //DB_DIR = "FLIGHT_LOGS/";
     //DB_DIR_STRING = "FLIGHT_LOGS/";
     //DB_NAME_BASE = "flight_";
     //DB_FILE_TYPE = ".db";
     //DB_MAX_FILES = 25;
//
     //TRANSACTION_MAX_DELAY_MS = 1000;
     //TRANSACTION_MIN_BATCH_SIZE = 10;
     //TRANSACTION_MAX_BATCH_SIZE = 15;
     //NUM_SQL_BINDED_STATEMENTS = 100;         // TEST : check during testing
     //NUM_SQL_UNBINDED_STATEMENTS_EACH_TABLE = 10;         // TEST : check during testing
//
     //MULTI_FILE_MODE = false;
     //DB_NAME = DB_DIR_STRING + "dev.db";

/*
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
*/
