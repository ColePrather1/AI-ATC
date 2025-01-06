#pragma once
#include "Common.h"
#include "Session.h"
#include "Packet.h"




struct MagnetPacket {
    //uint8_t id = Packet::PacketType::MAGNET_PACKET;
    uint8_t id = PacketType::MAGNET;
    int16_t x, y, z;

    // constructor for 3 inputs
    MagnetPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

