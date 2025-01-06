#pragma once
#include "common.h"
#include "Session.h"
#include "Packet.h"



class Frag : public Packet {
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













