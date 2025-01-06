#pragma once
#include "common.h"
#include "session.h"
#include "Packet.h"






struct GyroPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;
    // constructor for 3 inputs
    GyroPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}