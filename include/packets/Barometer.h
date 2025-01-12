#ifndef BAROMETER_H
#define BAROMETER_H
#pragma once

#include "Packet.h"

class BarometerPacket : public Packet {
public:
    int16_t pressure, temperature, baro_altitude;
    BarometerPacket(int16_t pressure, int16_t temperature, int16_t baro_altitude);
    void process() override;
};


#endif // BAROMETER_H