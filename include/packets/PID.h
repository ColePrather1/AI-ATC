#pragma once
#include "common.h"
#include "session.h"
#include "Packet.h"



// Logging PID Parameters
struct PIDPacket {
    //std::chrono::system_clock::time_point time;
    uint32_t timestamp;
    uint8_t id;
    char header;
    float p, i, d;

};

