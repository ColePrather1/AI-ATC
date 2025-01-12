#ifndef GPS_ENV_H
#define GPS_ENV_H
#pragma once
#include "Packet.h"

// 6 bytes

class GPSEnvPacket : public Packet {
public:
    uint16_t heading;
    uint16_t speed;
    uint8_t sats;
    uint8_t signal_strength;

    GPSEnvPacket();
    GPSEnvPacket(char hdr, uint16_t heading, uint16_t speed, uint8_t sats, uint8_t signal_strenght);
    void process() override;

};

#endif // GPS_ENV_H