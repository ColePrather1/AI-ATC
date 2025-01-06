#pragma once
#include "common.h"
#include "session.h"
#include "Packet.h"



struct AccelPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;

    // constructor for 3 inputs
    AccelPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}



/*
struct IMUDataPacket {
    uint8_t id;
    int16_t x, y, z;
    IMUDataPacket( uint8_t id, int16_t x, int16_t y, int16_t z) : id(id), x(x), y(y), z(z) {}
};
*/




/*
struct AccelPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;

    // constructor for 3 inputs
    AccelPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

struct GyroPacket {
    uint8_t id = ACCEL_PACKET; 
    int16_t x, y, z;
    // constructor for 3 inputs
    GyroPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

struct MagnetPacket {
    uint8_t id = MAGNET_PACKET;
    int16_t x, y, z;

    // constructor for 3 inputs
    MagnetPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
}

*/





