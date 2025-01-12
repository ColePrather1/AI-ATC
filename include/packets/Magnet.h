#ifndef MAGNET_H
#define MAGNET_H
#pragma once
#include "Packet.h"

class MagnetPacket : public Packet {
public:
    //PacketType type = PacketType::MAGNET;
    int16_t x, y, z;  // = x, y, z * 100 (e^2)
    //uint16_t x, y, z;

    // constructor for 3 inputs
    MagnetPacket(char hdr, int16_t x, int16_t y, int16_t z);
    void process() override;
};


#endif // MAGNET_H