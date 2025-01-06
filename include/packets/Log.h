#pragma once
#include "common.h"
#include "session.h"
#include "Packet.h"



// Logging Strings from PILOT
struct LogPacket {                 // Data packet

    //std::chrono::system_clock::time_point timestamp;
    //char header;
    //std::chrono::system_clock::time_point time;
    //std::array<char, 31> payload; 
    char payload[16];

    //std::timestamp time;
    // Add other relevant data fields
};