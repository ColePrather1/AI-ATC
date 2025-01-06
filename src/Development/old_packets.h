#pragma once
#include "common.h"
#include "session.h"
#include <chrono>

// PACKET CHAR NAMES
#define SOH 0x01  // Start of Header
#define NULL_CHAR 0x00  // Null character
#define STX 0x02  // Start of Text
#define ETX 0x03  // End of Text
#define EOT 0x04  // End of Transmission
#define RECSEP 0x1E  // Record Seporator


/*
enum PacketType {
    MANUAL_PACKET = 0,
    AUTO_PACKET = 1,
    GPS_PACKET = 2,
    ACCEL_PACKET = 3,
    GYRO_PACKET = 4,
    MAGNET_PACKET = 5,
    BARO_PACKET = 6,
    SYSTEM_PACKET = 7,
    EMERGENCY_PACKET = 8,
    STATUS_PACKET = 9,
    GPS_ENV_PACKET = 10,
};
*/

enum class PacketType : uint8_t {
    BASE,

    // System Data
    SYSTEM_PACKET,
    STATUS_PACKET,

    // Pairing
    PAIRING_PACKET,

    // Control Modes
    AUTO_PACKET,
    ASSIST_PACKET,
    MANUAL_PACKET,

    // IMU Data     // (d, x,y,z) in each packet
    ACCEL_PACKET,
    GYRO_PACKET,
    MAGNET_PACKET,

    // GPS Data
    GPS_PACKET,
    GPS_ENV_PACKET,

    // Sensor Data
    BAROMETER_PACKET,       // LPS22HB
    TEMP_HUMID_PACKET,      // HS3003
    //MIC_PACKET,           // MP34DT06JTR
    //GESTURE_PACKET,       // APDS9960
    //LIDAR_PACKET,         // TF-Luna

    // Acknowledgement
    ACK

};



class Packet {
public:
    PacketType type;
    //std::chrono::system_clock::time_point timestamp;
    uint32_t timestamp;
    char header;

    //virtual char[PAYLOAD_SIZE] payload;
    virtual char payload[PAYLOAD_SIZE] = {0};


    //char getHeader() const { return header; }
    //void setHeader(char hdr) { header = hdr; }
    //PacketType getType() const { return type; }
    //std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }



    //Packet(PacketType t) : type(t), timestamp(std::chrono::system_clock::now()) {}
    
    // Constructors
    Packet() : type(PacketType::BASE), header(0), timestamp(0) {}
    Packet(PacketType t) : type(t), header(0), timestamp(0) {}
    Packet(PacketType t, char hdr, uint32_t& time) : type(t), header(hdr), timestamp(time) {}

    virtual ~Packet() = default;
    virtual void serialize(char* buffer) const = 0;
    virtual void deserialize(const char* buffer) = 0;
};


class ManualPacket : public Packet {
public:
    char payload[PAYLOAD_SIZE];

    //ManualPacket() : Packet(PacketType::MANUAL_PACKET) {
    //    std::memset(payload, 0, PAYLOAD_SIZE);
    //}

    ManualPacket(char hdr, const char* pld) : Packet(PacketType::MANUAL_PACKET), header(hdr) {
        std::memcpy(payload, pld, PAYLOAD_SIZE);
    }

    ManualPacket(char hdr, const char* pld, uint32_t& time) : Packet(PacketType::MANUAL_PACKET, hdr, time) {
        std::memcpy(payload, pld, PAYLOAD_SIZE);
    }

    //char getHeader() const { return header; }
    //void setHeader(char hdr) { header = hdr; }

    const char* getPayload() const { return payload; }
    void setPayload(const char* pld) {
        std::memcpy(payload, pld, PAYLOAD_SIZE);
    }

    void serialize(char* buffer) const override {
        // Implement serialization
    }

    void deserialize(const char* buffer) override {
        // Implement deserialization
    }
};


struct IMUDataPacket {
    uint8_t id;
    int16_t x, y, z;
    IMUDataPacket( uint8_t id, int16_t x, int16_t y, int16_t z) : id(id), x(x), y(y), z(z) {}
};



    
/*
struct AccelPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;

    // constructor for 3 inputs
    AccelPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

struct GyroPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;
    // constructor for 3 inputs
    GyroPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

struct MagnetPacket {
    uint8_t id = MAGNET_PACKET;
    int16_t x, y, z;

    // constructor for 3 inputs
    MagnetPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

*/


/*
struct GPSData {
  float lat;
  float lon;
  float alt;
  float speed;
  int satellites;
  unsigned long timestamp;
  char header;
};

*/


struct GPSPacket {
    uint8_t id = GPS_PACKET;

    //float latitude;
    //float longitude;
    //float altitude;

    int32_t lat;  // Latitude * 1e7 (degrees)
    int32_t lon;  // Longitude * 1e7 (degrees)
    int16_t alt;  // Altitude in meters
    //uint8_t sats; // Number of satellites
    //unsigned long timestamp;

};

struct GPSEnvPacket {
    uint8_t id = GPS_ENV_PACKET;

    //float latitude;
    //float longitude;
    //float altitude;
    int32_t course;
    int32_t speed;
    uint8_t sats;
    unsigned long timestamp;
};



struct IMUEnvPacket {

    uint8_t id;

    float pressure;
    float temperature;
    float baro_altitude;
    float humidity;

};

struct PIDPacket {
    std::chrono::system_clock::time_point time;
    uint8_t id;
    char header;
    float p, i, d;

};



struct DataPacket {                 // Data packet

    //std::chrono::system_clock::time_point timestamp;
    char header;
    std::chrono::system_clock::time_point time;
    //std::array<char, 31> payload; 
    char payload[16];

    //std::timestamp time;
    // Add other relevant data fields
};


struct SystemPacket {                 // System packet

    //std::chrono::system_clock::time_point timestamp;
    char header;
    std::chrono::system_clock::time_point time;
    //std::array<char, 31> payload; 
    char payload[16];

    //std::timestamp time;
    // Add other relevant data fields
};





struct ManualPacket {
  //std::chrono::system_clock::time_point time;
  char header;
  char payload[PAYLOAD_SIZE];

  // constructor for 2 inputs header and payload
  //ManualPacket(char hdr, char pld[PAYLOAD_SIZE]) : header(hdr), payload(pld) {}

    // Default constructor
    ManualPacket() : header(0) {
        std::memset(payload, 0, PAYLOAD_SIZE);
    }

    // Constructor
    ManualPacket(char hdr, const char* pld) : header(hdr) {
        std::memcpy(payload, pld, PAYLOAD_SIZE);
    }

    ManualPacket(ManualPacket&& other) noexcept 
        : header(other.header) {
        std::memcpy(payload, other.payload, PAYLOAD_SIZE);
    }


    inline char getHeader() const { return header; }
    inline void setHeader(char hdr) { header = hdr; }


    const char* getPayload() const { return payload; }
    void setPayload(const char* pld) {
        std::memcpy(payload, pld, PAYLOAD_SIZE);
    }

};


const char sample_mp_packet[PAYLOAD_SIZE] = {
    SOH,        // Start of Header
    'S',        // Packet type identifier (e.g., 'S' for Servo)
    STX,        // Start of Text
    '1',        // Servo 1 value (3 digits)
    '2',
    '3',
    RECSEP,     // Record Separator
    '4',        // Servo 2 value
    '5',
    '6',
    RECSEP,
    '7',        // Servo 3 value
    '8',
    '9',
    RECSEP,
    '0',        // Servo 4 value
    '1',
    '2',
    RECSEP,
    '3',        // Servo 5 value
    '4',
    '5',
    ETX,        // End of Text
    EOT,        // End of Transmission
    //0x7F,       // Checksum (example value)
    //NULL_CHAR,  // Padding
    //NULL_CHAR,
    //NULL_CHAR,
    //NULL_CHAR,
    //NULL_CHAR,
    //NULL_CHAR
};