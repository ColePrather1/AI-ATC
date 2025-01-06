#pragma once
#include "common.h"
#include "session.h"

#include <sqlite3.h>
#include <iomanip>
#include <sstream>

//#include <iostream>
//#include <cstring>
//#include <chrono>

class DatabaseManager {
private:
    sqlite3* db;
    char* errorMessage;

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

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

    bool createTables() {
        const char* sql[] = {
            "CREATE TABLE IF NOT EXISTS SystemPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "system_data TEXT"
            ");",

            "CREATE TABLE IF NOT EXISTS StatusPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "status_data TEXT"
            ");",

            "CREATE TABLE IF NOT EXISTS PairingPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "pairing_data TEXT"
            ");",

            "CREATE TABLE IF NOT EXISTS ControlPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "packet_type TEXT,"
            "throttle INTEGER,"
            "elevator INTEGER,"
            "rudder INTEGER,"
            "left_aileron INTEGER,"
            "right_aileron INTEGER"
            ");",

            "CREATE TABLE IF NOT EXISTS IMUPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "packet_type TEXT,"
            "x REAL,"
            "y REAL,"
            "z REAL"
            ");",

            "CREATE TABLE IF NOT EXISTS GPSPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "latitude REAL,"
            "longitude REAL,"
            "altitude REAL,"
            "speed REAL"
            ");",

            "CREATE TABLE IF NOT EXISTS GPSEnvPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "env_data TEXT"
            ");",

            "CREATE TABLE IF NOT EXISTS BarometerPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "pressure REAL,"
            "temperature REAL"
            ");",

            "CREATE TABLE IF NOT EXISTS TempHumidPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "temperature REAL,"
            "humidity REAL"
            ");",

            "CREATE TABLE IF NOT EXISTS AckPackets ("
            "timestamp TEXT PRIMARY KEY,"
            "header CHAR(1),"
            "ack_data TEXT"
            ");"

            /*
            ,"CREATE TABLE IF NOT EXISTS ManualPacket ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "header CHAR(1),"
                          "throttle INTEGER,"
                          "elevator INTEGER,"
                          "rudder INTEGER,"
                          "left_aileron INTEGER,"
                          "right_aileron INTEGER,"
                          "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                          ");"
            */
      
        };

        for (const char* table_sql : sql) {
            int rc = sqlite3_exec(db, table_sql, nullptr, nullptr, &errorMessage);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errorMessage << std::endl;
                sqlite3_free(errorMessage);
                return false;
            }
        }
        return true;
    }

    bool insertPacket(const Packet& packet) {
        std::string sql;
        std::string timestamp = getCurrentTimestamp();

        switch (packet.type) {
            case PacketType::SYSTEM_PACKET:
                sql = "INSERT INTO SystemPackets (timestamp, header, system_data) VALUES (?, ?, ?);";
                break;
            case PacketType::STATUS_PACKET:
                sql = "INSERT INTO StatusPackets (timestamp, header, status_data) VALUES (?, ?, ?);";
                break;
            case PacketType::PAIRING_PACKET:
                sql = "INSERT INTO PairingPackets (timestamp, header, pairing_data) VALUES (?, ?, ?);";
                break;
            case PacketType::AUTO_PACKET:
            case PacketType::ASSIST_PACKET:
            case PacketType::MANUAL_PACKET:
                sql = "INSERT INTO ControlPackets (timestamp, header, packet_type, throttle, elevator, rudder, left_aileron, right_aileron) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
                break;
            case PacketType::ACCEL_PACKET:
            case PacketType::GYRO_PACKET:
            case PacketType::MAGNET_PACKET:
                sql = "INSERT INTO IMUPackets (timestamp, header, packet_type, x, y, z) VALUES (?, ?, ?, ?, ?, ?);";
                break;
            case PacketType::GPS_PACKET:
                sql = "INSERT INTO GPSPackets (timestamp, header, latitude, longitude, altitude, speed) VALUES (?, ?, ?, ?, ?, ?);";
                break;
            case PacketType::GPS_ENV_PACKET:
                sql = "INSERT INTO GPSEnvPackets (timestamp, header, env_data) VALUES (?, ?, ?);";
                break;
            case PacketType::BAROMETER_PACKET:
                sql = "INSERT INTO BarometerPackets (timestamp, header, pressure, temperature) VALUES (?, ?, ?, ?);";
                break;
            case PacketType::TEMP_HUMID_PACKET:
                sql = "INSERT INTO TempHumidPackets (timestamp, header, temperature, humidity) VALUES (?, ?, ?, ?);";
                break;
            case PacketType::ACK:
                sql = "INSERT INTO AckPackets (timestamp, header, ack_data) VALUES (?, ?, ?);";
                break;
            default:
                std::cerr << "Unknown packet type" << std::endl;
                return false;
        }

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, timestamp.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, &packet.header, 1, SQLITE_STATIC);

        const char* payload = packet.getPayload();
        switch (packet.type) {
            case PacketType::SYSTEM_PACKET:
            case PacketType::STATUS_PACKET:
            case PacketType::PAIRING_PACKET:
            case PacketType::GPS_ENV_PACKET:
            case PacketType::ACK:
                sqlite3_bind_text(stmt, 3, payload, -1, SQLITE_STATIC);
                break;
            case PacketType::AUTO_PACKET:
            case PacketType::ASSIST_PACKET:
            case PacketType::MANUAL_PACKET:
                {
                    const char* packet_type = (packet.type == PacketType::AUTO_PACKET) ? "AUTO" :
                                              (packet.type == PacketType::ASSIST_PACKET) ? "ASSIST" : "MANUAL";
                    sqlite3_bind_text(stmt, 3, packet_type, -1, SQLITE_STATIC);
                    for (int i = 0; i < 5; ++i) {
                        int value = (payload[3 + i * 4] - '0') * 100 +
                                    (payload[4 + i * 4] - '0') * 10 +
                                    (payload[5 + i * 4] - '0');
                        sqlite3_bind_int(stmt, i + 4, value);
                    }
                }
                break;
            case PacketType::ACCEL_PACKET:
            case PacketType::GYRO_PACKET:
            case PacketType::MAGNET_PACKET:
                {
                    const char* packet_type = (packet.type == PacketType::ACCEL_PACKET) ? "ACCEL" :
                                              (packet.type == PacketType::GYRO_PACKET) ? "GYRO" : "MAGNET";
                    sqlite3_bind_text(stmt, 3, packet_type, -1, SQLITE_STATIC);
                    for (int i = 0; i < 3; ++i) {
                        float value;
                        std::memcpy(&value, payload + 1 + i * sizeof(float), sizeof(float));
                        sqlite3_bind_double(stmt, i + 4, value);
                    }
                }
                break;
            case PacketType::GPS_PACKET:
            case PacketType::BAROMETER_PACKET:
            case PacketType::TEMP_HUMID_PACKET:
                for (int i = 0; i < 4; ++i) {
                    float value;
                    std::memcpy(&value, payload + 1 + i * sizeof(float), sizeof(float));
                    sqlite3_bind_double(stmt, i + 3, value);
                }
                break;
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
    
    if (!dbManager.openDatabase("flight_data.db")) {
        return 1;
    }
    
    if (!dbManager.createTables()) {
        return 1;
    }

    std::cout << "Database and tables created successfully." << std::endl;
    return 0;
}
