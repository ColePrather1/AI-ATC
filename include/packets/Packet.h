#ifndef PACKET_H
#define PACKET_H

#pragma once
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
    SYSTEM,
    STATUS,
    // Pairing
    PAIRING,
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
    ACK
};





class Packet {
public:

    //PacketType::PacketType type;

    // 2^4 = 16

    PacketType type;

    //std::chrono::system_clock::time_point timestamp;
    //uint32_t timestamp;
    
    char header;
    //void* payload;

    //virtual char[PAYLOAD_SIZE] payload;
    //virtual char payload[PAYLOAD_SIZE] = {0};


    //char getHeader() const { return header; }
    //void setHeader(char hdr) { header = hdr; }
    //PacketType getType() const { return type; }
    //std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }



    //Packet(PacketType t) : type(t), timestamp(std::chrono::system_clock::now()) {}

/*
Getters & Setters
*/
    char getHeader() const { return header; }
    void setHeader(char hdr) { header = hdr; }


/*  
Constructors
*/
    // Default Constructor
    //Packet() : type(PacketType::BASE), header(0), timestamp(0) {}
    Packet() : type(PacketType::BASE), header(0) {}
    // Type-only Constructor
    //Packet(PacketType t) : type(t), header(0), timestamp(0) {}
    // Type, Header, Time Constructor
    //Packet(PacketType t, char hdr, uint32_t& time) : type(t), header(hdr), timestamp(time) {}
    Packet(PacketType t, char hdr) : type(t), header(hdr) {}



/*
Destructors / Virtual
*/
    virtual ~Packet() = default;

    virtual char* getPayload() = 0;
    virtual const char* getPayload() const = 0;
    virtual void setPayload(const void* data) = 0;
    virtual bool process() = 0;


    //virtual void serialize(char* buffer) const = 0;     // Encode
    //virtual void deserialize(const char* buffer) = 0;   // Decode
    //virtual void encode(char* buffer) const = 0;     // Encode
    //virtual void decode(const char* buffer) = 0;   // Decode

};






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


#endif // PACKET_H