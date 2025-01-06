
#include "common.h"
//#include "Session.h"
#include "SQL.h"
//#include <sqlite3.h>
#include <filesystem>

#include <fstream>



bool DBsetup(){
    if (openDB()) {
        return 1;
    }

    // USE IN THE FUTURE, WHEN SQLITE APP/POWER IS RELIABLE // Optimize for performance
    //sqlite3_exec(DB, "PRAGMA synchronous = OFF", NULL, NULL, NULL);   // Can corrupt db if power lost // Up to 50x faster or more
    //sqlite3_exec(DB, "PRAGMA journal_mode = MEMORY", NULL, NULL, NULL); // Very dangerous // Can corrupt db if power lost, app crashes // Fastest possible performance

    // Safer, but slower alternatives // Optimize for performance
    sqlite3_exec(DB, "PRAGMA journal_mode = WAL", NULL, NULL, NULL);
    sqlite3_exec(DB, "PRAGMA synchronous = NORMAL", NULL, NULL, NULL);


/*
    if (createSchema()) {
        return 1;
    }
*/
    return 0;
}

/*
bool createSchema(){

    // Read SQL file
    std::ifstream sqlFile("schema.sql");
    std::string sql((std::istreambuf_iterator<char>(sqlFile)),
                     std::istreambuf_iterator<char>());

    // Execute SQL   
    std::string schema = getSchema();
    rc = sqlite3_exec(db, schema.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    } else {
        std::cout << "Database schema created successfully" << std::endl;
        return 0;
    }
}
*/

bool openDB(){
    std::string filename = getFilename();
    rc = sqlite3_open(filename.c_str(), &DB);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(DB) << std::endl;
        return 1;
    }
    else {
        std::cout << "Opened database successfully :  " << filename << std::endl;
        return 0;
    }
}

bool closeDB(){
    rc = sqlite3_close(DB);
    if (rc) {
        std::cerr << "Can't close database: " << sqlite3_errmsg(DB) << std::endl;
        return 1;
    }
    else {
        std::cout << "Closed database successfully" << std::endl;
        return 0;
    }
}


/*
std::string getFilename(){
    if (MULTI_FILE_MODE){
        //return getNextUniqueFilename();
        std::string filename = getNextUniqueFilename();
        if (filename == "") {
            std::cerr << "Unable to find an available filename in " << DB_DIR << std::endl;
        }
        return filename;


    } else {
        return DB_NAME;
    }
}
*/

std::string getNextUniqueFilename() {
    int suffix = 0;
    std::string filename = "";
    
    while (true && suffix < DB_MAX_FILES) {
        filename = DB_DIR + DB_NAME_BASE + std::to_string(suffix) + DB_FILE_TYPE;
        
        if (!std::filesystem::exists(filename)) {
            return filename;
        }
        
        suffix++;
    }
    return "";
}








