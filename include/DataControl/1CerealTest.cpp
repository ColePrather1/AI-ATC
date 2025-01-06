#pragma once
//#include "common.h"
//#include "Session.h"

#include <array>
#include <vector>
//#include <string>
//#include <cstring>
//#include <algorithm>

// PACKET CHAR NAMES
#define SOH 0x01  // Start of Header
#define NULL_CHAR 0x00  // Null character
#define STX 0x02  // Start of Text
#define ETX 0x03  // End of Text
#define EOT 0x04  // End of Transmission
#define RECSEP 0x1E  // Record Seporator



#define PAYLOAD_SIZE 24
#define NUM_FEATS 5
#define MAX_PACKET_SIZE 32


#include <bitset>

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


struct PacketHeader {
    uint16_t sequence_id;
    //uint2_t total_fragments;
    //uint2_t fragment_number;

    std::bitset<4> fields;
    // Max 4 Fragments
    // Bits 0-1 : Total Fragments
    // Bits 2-3 : Fragment Number


    PacketHeader() : sequence_id(0), fields(0) {}

    // Setter methods
    void setTotalFragments(uint8_t total) {
        fields[0] = total & 1;
        fields[1] = (total >> 1) & 1;
    }

    void setFragmentNumber(uint8_t number) {
        fields[2] = number & 1;
        fields[3] = (number >> 1) & 1;
    }

    // Getter methods
    uint8_t getTotalFragments() const {
        return (fields[1] << 1) | fields[0];
    }

    uint8_t getFragmentNumber() const {
        return (fields[3] << 1) | fields[2];
    }


};


//int n_frags = (data.size() + MAX_PAYLOAD_SIZE - 1) / MAX_PAYLOAD_SIZE;
//template <typename T, int n_frags = (payload.size() + MAX_PACKET_SIZE - 1) / MAX_PACKET_SIZE>
class Packet {
public:

    //PacketType::PacketType type;
    PacketType type;
    //std::chrono::system_clock::time_point timestamp;
    uint32_t timestamp;
    char header;
    char payload[PAYLOAD_SIZE];

    //static const int n_bits; // = sizeof(Packet) * 8;
    //static constexpr int n_bits;// = sizeof(Packet) * 8;
    static constexpr int n_bits = 8;// = sizeof(Packet) * 8;
    std::bitset<n_bits>& myBitset;

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
    Packet() : type(PacketType::BASE), header('0'), timestamp(0) {}
    // Type-only Constructor
    Packet(PacketType ptype) : type(ptype), header('0'), timestamp(0) {}
    //Packet(PacketType t) : type(t), header(0), timestamp(0) {}
    // Type, Header, Time Constructor
    Packet(PacketType t, char hdr, uint32_t time) : type(t), header(hdr), timestamp(time) {}
    //Packet(PacketType t, char hdr, uint32_t& time) : type(t), header(hdr), timestamp(time) {}
    

/*
Destructors / Virtual
*/
    virtual ~Packet() = default;

    virtual char* getPayload() = 0;
    virtual const char* getPayload() const = 0;
    virtual void setPayload(const void* data) = 0;


    //virtual void serialize(char* buffer) const = 0;     // Encode
    //virtual void deserialize(const char* buffer) = 0;   // Decode
    //virtual void encode(char* buffer) const = 0;     // Encode
    //virtual void decode(const char* buffer) = 0;   // Decode

};

//n_bits = sizeof(Packet) * 8;
//int n_bits = sizeof(Packet) * 8;





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






class ManualPacket : public Packet {
public:
    uint8_t* vals[NUM_FEATS];

    //ManualPacket() : Packet(PacketType::MANUAL_PACKET) {
    //    std::memset(payload, 0, PAYLOAD_SIZE);
    //}

    // Default constructor
    ManualPacket() : Packet(PacketType::MANUAL) {
        std::memset(payload, 0, PAYLOAD_SIZE);
    }

    ManualPacket(char hdr, uint8_t* vals[NUM_FEATS]) : Packet(PacketType::MANUAL, hdr, (uint32_t)0) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        setPayload(vals);
    }

    ManualPacket(char hdr, uint8_t* vals[NUM_FEATS], uint32_t time) : Packet(PacketType::MANUAL, hdr, time) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        setPayload(vals);
    }

    // Pre-packed payload constructor
    ManualPacket(char hdr, const char* pld, uint32_t time) : Packet(PacketType::MANUAL, hdr, time) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        setPayload(pld);
    }



    static constexpr int BITSET_SIZE = sizeof(Packet) * 8;
    std::bitset<BITSET_SIZE> serialize() const {
        std::bitset<BITSET_SIZE> bits;
        size_t bitIndex = 0;

        // Serialize Packet base class members
        for (size_t i = 0; i < sizeof(PacketType); ++i) {
            uint8_t byte = static_cast<uint8_t>(type) >> (i * 8);
            for (int j = 0; j < 8; ++j) {
                bits[bitIndex++] = (byte >> j) & 1;
            }
        }

        for (size_t i = 0; i < sizeof(timestamp); ++i) {
            uint8_t byte = (timestamp >> (i * 8)) & 0xFF;
            for (int j = 0; j < 8; ++j) {
                bits[bitIndex++] = (byte >> j) & 1;
            }
        }

        for (int i = 0; i < 8; ++i) {
            bits[bitIndex++] = (header >> i) & 1;
        }

        // Serialize ManualPacket payload
        for (size_t i = 0; i < PAYLOAD_SIZE; ++i) {
            for (int j = 0; j < 8; ++j) {
                bits[bitIndex++] = (payload[i] >> j) & 1;
            }
        }

        // Serialize vals array
        for (int i = 0; i < NUM_FEATS; ++i) {
            for (int j = 0; j < 8; ++j) {
                bits[bitIndex++] = (*vals[i] >> j) & 1;
            }
        }

        return bits;
    }





    const char* getPayload() const override {
        return payload;
    }


    void setPayload(const char* pld)   {
        std::memcpy(payload, pld, PAYLOAD_SIZE);      // char[] only
    }

    // Auto-encodes from int[] -> char[]                    /*  FUTURE: Auto-size by NUM_FEATS   */
    //void setPayload(const char* pld) {
    void setPayload(uint8_t* vals[NUM_FEATS]) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);      // char[] only
        payload = {
            SOH,                               // Start of Header
            header,                            // Packet type identifier (e.g., 'S' for Servo)
            STX,                               // Start of Text , Throttle    
            '0' + (vals[0] / 100) % 10,        // Hundreds place
            '0' + (vals[0] / 10) % 10,         // Tens place
            '0' + vals[0] % 10,
            RECSEP,
            '0' + (vals[1] / 100) % 10,        // Elevator
            '0' + (vals[1] / 10) % 10,
            '0' + vals[1] % 10,
            RECSEP,
            '0' + (vals[2] / 100) % 10,        // Rudder
            '0' + (vals[2] / 10) % 10,
            '0' + vals[2] % 10,
            RECSEP,
            '0' + (vals[3] / 100) % 10,        // Left Aileron
            '0' + (vals[3] / 10) % 10,
            '0' + vals[3] % 10,
            RECSEP,
            '0' + (vals[4] / 100) % 10,        // Right Aileron
            '0' + (vals[4] / 10) % 10,
            '0' + vals[4] % 10,
            ETX,                               // End of Text
            EOT                                // End of Transmission

        };

    }

};


/*
    void encode(char* buffer) const override {
        //char data[PAYLOAD_SIZE] = {

        SOH,        // Start of Header
        header,        // Packet type identifier (e.g., 'S' for Servo)
        STX,        // Start of Text , Throttle    
        '0' + (vals[0] / 100) % 10,  // Hundreds place
        '0' + (vals[0] / 10) % 10,   // Tens place
        '0' + vals[0] % 10,
        RECSEP,
        '0' + (vals[1] / 100) % 10,        // Elevator
        '0' + (vals[1] / 10) % 10,
        '0' + vals[1] % 10,
        RECSEP,
        '0' + (vals[2] / 100) % 10,        // Rudder
        '0' + (vals[2] / 10) % 10,
        '0' + vals[2] % 10,
        RECSEP,
        '0' + (vals[3] / 100) % 10,        // Left Aileron
        '0' + (vals[3] / 10) % 10,
        '0' + vals[3] % 10,
        RECSEP,
        '0' + (vals[4] / 100) % 10,        // Right Aileron
        '0' + (vals[4] / 10) % 10,
        '0' + vals[4] % 10,
        ETX,        // End of Text
        EOT        // End of Transmission

        }
    }
*/

/*
    void decode(const char* buffer) override {
        // Implement deserialization
    }
*/

//};













