#pragma once
#include "common.h"
#include "Session.h"

#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include "DatabasePacket.hpp"

// DatabaseManager.h
// (Previous code remains the same)

public:
    // (Previous methods remain the same)
    bool insertPacket(const DatabasePacket& packet);

// DatabaseManager.cpp
// (Previous code remains the same)

bool DatabaseManager::insertPacket(const DatabasePacket& packet) {
    std::string sql;
    std::vector<std::variant<int, float, std::string>> values;

    switch (packet.getType()) {
        case DatabasePacket::PacketType::SYSTEM:
            sql = "INSERT INTO SystemPackets (timestamp, header, system_data) VALUES (?, ?, ?);";
            break;
        case DatabasePacket::PacketType::STATUS:
            sql = "INSERT INTO StatusPackets (timestamp, header, status_data) VALUES (?, ?, ?);";
            break;
        case DatabasePacket::PacketType::PAIRING:
            sql = "INSERT INTO PairingPackets (timestamp, header, pairing_data) VALUES (?, ?, ?);";
            break;
        case DatabasePacket::PacketType::CONTROL:
            sql = "INSERT INTO ControlPackets (timestamp, header, packet_type, throttle, elevator, rudder, left_aileron, right_aileron) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
            break;
        case DatabasePacket::PacketType::IMU:
            sql = "INSERT INTO IMUPackets (timestamp, header, packet_type, x, y, z) VALUES (?, ?, ?, ?, ?, ?);";
            break;
        case DatabasePacket::PacketType::GPS:
            sql = "INSERT INTO GPSPackets (timestamp, header, latitude, longitude, altitude, speed) VALUES (?, ?, ?, ?, ?, ?);";
            break;
        case DatabasePacket::PacketType::GPS_ENV:
            sql = "INSERT INTO GPSEnvPackets (timestamp, header, env_data) VALUES (?, ?, ?);";
            break;
        case DatabasePacket::PacketType::BAROMETER:
            sql = "INSERT INTO BarometerPackets (timestamp, header, pressure, temperature) VALUES (?, ?, ?, ?);";
            break;
        case DatabasePacket::PacketType::TEMP_HUMID:
            sql = "INSERT INTO TempHumidPackets (timestamp, header, temperature, humidity) VALUES (?, ?, ?, ?);";
            break;
        case DatabasePacket::PacketType::ACK:
            sql = "INSERT INTO AckPackets (timestamp, header, ack_data) VALUES (?, ?, ?);";
            break;
        case DatabasePacket::PacketType::TIMESTAMP_STRING:
            sql = "INSERT INTO TimestampStrings (timestamp, string_data) VALUES (?, ?);";
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

    sqlite3_bind_text(stmt, 1, packet.getTimestamp().c_str(), -1, SQLITE_STATIC);
    
    if (packet.getType() != DatabasePacket::PacketType::TIMESTAMP_STRING) {
        sqlite3_bind_text(stmt, 2, &packet.getHeader(), 1, SQLITE_STATIC);
    }

    const auto& data = packet.getData();
    for (size_t i = 0; i < data.size(); ++i) {
        int index = i + (packet.getType() == DatabasePacket::PacketType::TIMESTAMP_STRING ? 2 : 3);
        const auto& value = data[i].second;
        
        if (std::holds_alternative<int>(value)) {
            sqlite3_bind_int(stmt, index, std::get<int>(value));
        } else if (std::holds_alternative<float>(value)) {
            sqlite3_bind_double(stmt, index, std::get<float>(value));
        } else if (std::holds_alternative<std::string>(value)) {
            sqlite3_bind_text(stmt, index, std::get<std::string>(value).c_str(), -1, SQLITE_STATIC);
        }
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}
