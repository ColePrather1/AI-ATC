#ifndef PACKET_HEADER_H
#define PACKET_HEADER_H

#include <cstdint>
#include "Bitmask.h"

struct PacketHeader
{
    Bitmask8 data;

    // PacketType - 4 bitSet

};


#endif // PACKET_HEADER_H