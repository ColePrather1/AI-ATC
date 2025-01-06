#ifndef PACKETS_H
#define PACKETS_H

#pragma once

//#include "Common.h"
//#include "Session.h"
#include <chrono>


#include "Packet.h"

#include "Pairing.h"
#include "Status.h"
#include "System.h"
#include "Log.h"
#include "PID.h"
//#include "Emergency.h"

#include "Manual.h"
#include "Auto.h"
#include "Assist.h"

#include "Accel.h"
#include "Gyro.h"
#include "Magnet.h"

#include "GPS.h"
#include "GPS_Env.h"


#include "Barometer.h"
#include "Temp-Humid.h"



int getPipe(const Packet& packet) {
    switch (packet.type) {
        case PacketType::SYSTEM:
        case PacketType::STATUS:
        case PacketType::PAIRING:
        case PacketType::ACK:
            return 0;

        case PacketType::AUTO:
            return 1;
        
        case PacketType::ASSIST:
        case PacketType::MANUAL:
            return 2;

        case PacketType::ACCEL:
        case PacketType::GYRO:
        case PacketType::MAGNET:
            return 3;

        case PacketType::GPS:
        case PacketType::GPS_ENV:
            return 4;
        
        case PacketType::BAROMETER:
        case PacketType::TEMP_HUMID:
        //case PacketType::SENSOR_PACKET:
            return 5;

        case PacketType::BASE:                      // No Pipe / Error Handling
        default:
            return -1;
    }
}






/*
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

*/


#endif // PACKETS_H