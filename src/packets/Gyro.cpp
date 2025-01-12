#include "packets/Gyro.h"
#include "Logging.h"
//#include "Session.h"
#include <stdint.h>


GyroPacket::GyroPacket() : Packet(PacketType::GYRO, 'y') {}

GyroPacket::GyroPacket(char hdr, int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z), Packet(PacketType::GYRO, hdr) {}


void GyroPacket::process() {
    //std::cout << "Processing Gyro Packet" << std::endl;
    Logging::insertGyroData(x, y, z);
    return;
}

