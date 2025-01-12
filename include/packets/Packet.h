#ifndef PACKET_H
#define PACKET_H
#pragma once
#pragma pack(push, 1)
#include <cstdint>

//#include "common.h"
//#include "Session.h"


// PACKET CHAR NAMES
#define SOH 0x01  // Start of Header
#define NULL_CHAR 0x00  // Null character
#define STX 0x02  // Start of Text
#define ETX 0x03  // End of Text
#define EOT 0x04  // End of Transmission
#define RECSEP 0x1E  // Record Seporator


enum class PacketType : uint8_t {
    BASE,
    // System Data
    //SYSTEM,
    //STATUS,
    PID,
    // Pairing
    //PAIRING,
    // Control Modes
    AUTO,
    ASSIST,
    MANUAL,
    // IMU Data     // (d, x,y,z) in each packet
    ACCEL,
    GYRO,
    MAGNET,
    // GPS Data
    GPS,
    GPS_ENV,
    // Sensor Data
    BAROMETER,       // LPS22HB
    TEMP_HUMID,      // HS3003
    //MIC_PACKET,           // MP34DT06JTR
    //GESTURE_PACKET,       // APDS9960
    //LIDAR_PACKET,         // TF-Luna
    // Acknowledgement
    //ACK,
    EVENT,
    //EVENT_DATA,
    EVENT_DATA8,
    EVENT_DATA16,
    EVENT_DATA32,
    EVENT_DATA64,
    EVENT_TIMED,
    EVENT_TIMED_DATA
};



// 2 bytes  // 8 bytes with process()
class Packet {
public:
    PacketType type;
    char header;



    Packet() : type(PacketType::BASE), header(0) {}
    Packet(PacketType t, char hdr) : type(t), header(hdr) {}
    virtual ~Packet() = default;



    virtual void process() = 0;


    //virtual void serialize(char* buffer) const = 0;     // Encode
    //virtual void deserialize(const char* buffer) = 0;   // Decode
};
 // } __attribute__((packed));






/*
    \/  \/  Old Code Storage Below  \/  \/
*/

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

#pragma pack(pop)
#endif // PACKET_H