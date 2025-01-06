#pragma once
#include "common.h"
#include "Session.h"

#include <sqlite3.h>
#include <iomanip>
#include <sstream>


#include <string>
#include <vector>
#include <chrono>

class DatabasePacket {
public:
    enum class PacketType {
        SYSTEM,
        STATUS,
        PAIRING,
        CONTROL,
        IMU,
        GPS,
        GPS_ENV,
        BAROMETER,
        TEMP_HUMID,
        ACK,
        TIMESTAMP_STRING
    };

    DatabasePacket(PacketType type);

    void setHeader(char header);
    void addIntData(const std::string& key, int value);
    void addFloatData(const std::string& key, float value);
    void addStringData(const std::string& key, const std::string& value);
    void setTimestamp(const std::string& timestamp);

    PacketType getType() const;
    char getHeader() const;
    const std::vector<std::pair<std::string, std::variant<int, float, std::string>>>& getData() const;
    std::string getTimestamp() const;

private:
    PacketType type;
    char header;
    std::vector<std::pair<std::string, std::variant<int, float, std::string>>> data;
    std::string timestamp;
};

// DatabasePacket.cpp
#include "DatabasePacket.h"

DatabasePacket::DatabasePacket(PacketType type) : type(type), header(0) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

void DatabasePacket::setHeader(char header) {
    this->header = header;
}

void DatabasePacket::addIntData(const std::string& key, int value) {
    data.emplace_back(key, value);
}

void DatabasePacket::addFloatData(const std::string& key, float value) {
    data.emplace_back(key, value);
}

void DatabasePacket::addStringData(const std::string& key, const std::string& value) {
    data.emplace_back(key, value);
}

void DatabasePacket::setTimestamp(const std::string& timestamp) {
    this->timestamp = timestamp;
}

DatabasePacket::PacketType DatabasePacket::getType() const {
    return type;
}

char DatabasePacket::getHeader() const {
    return header;
}

const std::vector<std::pair<std::string, std::variant<int, float, std::string>>>& DatabasePacket::getData() const {
    return data;
}

std::string DatabasePacket::getTimestamp() const {
    return timestamp;
}










