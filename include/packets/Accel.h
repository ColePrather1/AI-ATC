#ifndef ACCEL_H
#define ACCEL_H
#pragma once
#include "Packet.h"
#include <cstdint>


class AccelPacket : public Packet {
public:
    int16_t x, y, z;  // = x, y, z * 100 
    //uint16_t x, y, z;

    // constructor for 3 inputs

    AccelPacket(int16_t x, int16_t y, int16_t z);
    void process() override;
};


#endif // ACCEL_H