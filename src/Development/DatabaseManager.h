#include <sqlite3.h>
#include <iostream>
#include <cstring>

class DatabaseManager {
private:
    sqlite3* db;
    char* errorMessage;

public:
    DatabaseManager() : db(nullptr), errorMessage(nullptr) {}

    ~DatabaseManager() {
        if (db) {
            sqlite3_close(db);
        }
    }

    bool openDatabase(const char* dbName) {
        int rc = sqlite3_open(dbName, &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    bool createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS ManualPacket ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "header CHAR(1),"
                          "throttle INTEGER,"
                          "elevator INTEGER,"
                          "rudder INTEGER,"
                          "left_aileron INTEGER,"
                          "right_aileron INTEGER,"
                          "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                          ");";

        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
            return false;
        }
        return true;
    }

    bool insertPacket(const ManualPacket& packet) {
        const char* sql = "INSERT INTO ManualPacket (header, throttle, elevator, rudder, left_aileron, right_aileron) "
                          "VALUES (?, ?, ?, ?, ?, ?);";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        const char* payload = packet.getPayload();
        sqlite3_bind_text(stmt, 1, &payload[1], 1, SQLITE_STATIC);
        
        for (int i = 0; i < 5; ++i) {
            int value = (payload[3 + i * 4] - '0') * 100 +
                        (payload[4 + i * 4] - '0') * 10 +
                        (payload[5 + i * 4] - '0');
            sqlite3_bind_int(stmt, i + 2, value);
        }

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }
};

int main() {
    DatabaseManager dbManager;
    
    if (!dbManager.openDatabase("packets.db")) {
        return 1;
    }
    
    if (!dbManager.createTable()) {
        return 1;
    }

    // Example usage:
    // ManualPacket packet;
    // packet.setPayload(sample_mp_packet);
    // dbManager.insertPacket(packet);

    std::cout << "Database and table created successfully." << std::endl;
    return 0;
}

















