#ifndef SYSTEM_H
#define SYSTEM_H

#pragma once

#include "Common.h"
#include "Session.h"
#include "Packet.h"

#include "Bitmask.h"


struct SystemPacket : public Packet {                 // System packet

    uint8_t event_type;

    //Bitmask payload;      // Bitmask payload


    //std::chrono::system_clock::time_point timestamp;
    //char header;
    //std::array<char, 31> payload; 
    //char payload[16];

    //Bitmask payload;

    //std::timestamp time;
    // Add other relevant data fields



};

#endif // SYSTEM_H