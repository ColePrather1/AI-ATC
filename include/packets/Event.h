#ifndef EVENT_H
#define EVENT_H

#pragma once

//#include "Common.h"
//#include "Session.h"

#include "Packet.h"

//#include "Bitmask.h"

#include "../src/EventTypes.h"


class EventPacket : public Packet {                 // System packet

    uint8_t event_type; // 6 bits
    uint8_t agree;      // 1 bit



    //Bitmask payload;      // Bitmask payload


    //std::chrono::system_clock::time_point timestamp;
    //char header;
    //std::array<char, 31> payload; 
    //char payload[16];

    //Bitmask payload;

    //std::timestamp time;
    // Add other relevant data fields



};

#endif // EVENT_H