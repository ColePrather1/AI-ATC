#ifndef TEMP_HUMID_H
#define TEMP_HUMID_H
#pragma once
#include "Packet.h"

class TempHumidPacket : public Packet {
public:
    uint16_t temp, humid;  // = x, y, z * 100 (e^2)
    //uint16_t x, y, z;

    TempHumidPacket(char hdr, uint16_t temp, uint16_t humid);
    void process() override;
};

#endif // TEMP_HUMID_H