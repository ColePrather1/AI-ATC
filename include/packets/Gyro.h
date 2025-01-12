#ifndef GYRO_H
#define GYRO_H
#pragma once
#include "Packet.h"

class GyroPacket : public Packet {
public:
    int16_t x, y, z;  // = x, y, z * 100 (e^2)

    GyroPacket();
    GyroPacket(char hdr, int16_t x, int16_t y, int16_t z);
    void process() override;
};


#endif // GYRO_H