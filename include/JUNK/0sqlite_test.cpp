#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>

#include "SQL.h"
#include <filesystem>



int main() {
    sqlite3* db;
    char* errMsg = nullptr;
    int rc;

    // Open database
    rc = sqlite3_open("data.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Read SQL file
    std::ifstream sqlFile("schema.sql");
    std::string sql((std::istreambuf_iterator<char>(sqlFile)),
                     std::istreambuf_iterator<char>());

    // Execute SQL
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Database schema created successfully" << std::endl;
    }

    // Close database
    sqlite3_close(db);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int insert_data(sqlite3* db) {
    char* errMsg = nullptr;
    int rc;

    rc = sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "BEGIN TRANSACTION failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }

    const char* sql = "INSERT INTO myclient (clientid, password, aflag, sflag) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // Insert multiple rows
    const char* clients[][4] = {
        {"mthomas", "mthomas", "0", "1"},
        {"pgeorge", "pgeorge", "1", "1"},
        {"jdoe", "jdoe", "0", "1"}
    };

    for (const auto& client : clients) {
        sqlite3_bind_text(stmt, 1, client[0], -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, client[1], -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, client[2], -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, client[3], -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Insertion failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return rc;
        }
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);

    rc = sqlite3_exec(db, "COMMIT;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "COMMIT failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }

    std::cout << "Data inserted successfully" << std::endl;
    return SQLITE_OK;
}





