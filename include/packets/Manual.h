#ifndef MANUAL_H
#define MANUAL_H

#pragma once

#include "Common.h"
#include "Session.h"
#include "Packet.h"


//PacketType::

class ManualPacket : public Packet {
public:

    //uint8_t* vals[NUM_FEATS];

    uint8_t throttle;
    uint8_t elevator;
    uint8_t rudder;
    uint8_t left_aileron;
    uint8_t right_aileron;

    // Default constructor
    ManualPacket() : Packet(PacketType::MANUAL) {
        //std::memset(payload, 0, PAYLOAD_SIZE);
    }

    ManualPacket(char hdr, uint8_t* vals[NUM_FEATS]) : Packet(PacketType::MANUAL, hdr, 0) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        self.setPayload(vals);
    }

    ManualPacket(char hdr, uint8_t* vals[NUM_FEATS], uint32_t time) : Packet(PacketType::MANUAL, hdr, time) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        self.setPayload(vals);
    }



/*
TODO: Implement processing
*/
    bool process() override {
        // Implement processing
        std::cout << "Processing Manual Packet" << std::endl;
        
        return true;
    }

};




    /*

    //char payload[PAYLOAD_SIZE];

    //ManualPacket() : Packet(PacketType::MANUAL_PACKET) {
    //    std::memset(payload, 0, PAYLOAD_SIZE);
    //}

    // Pre-packed payload constructor
    ManualPacket(char hdr, const char* pld, uint32_t time) : Packet(PacketType::MANUAL, hdr, time) {
        //std::memcpy(payload, pld, PAYLOAD_SIZE);
        self.setPayload(pld);
    }
    const char* getPayload() const override {
        return payload;
    }
    void setPayload(const char* pld) override  {
        std::memcpy(payload, pld, PAYLOAD_SIZE);      // char[] only
    }
    

    // Auto-encodes from int[] -> char[]                    //  FUTURE: Auto-size by NUM_FEATS   
    //void setPayload(const char* pld) {
    void setPayload(uint8_t* vals[NUM_FEATS]) override{
        //std::memcpy(payload, pld, PAYLOAD_SIZE);      // char[] only
        self.payload = {
            SOH,                               // Start of Header
            self.header,                            // Packet type identifier (e.g., 'S' for Servo)
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

        }

    }
    */




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




#endif // MANUAL_H