
#include "packets/Accel.h"

#include "Logging.h"
//#include "Packet.h"
//#include <cstdint>

AccelPacket::AccelPacket(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z), Packet(PacketType::ACCEL, 'a') {}

void AccelPacket::process() {
    //std::cout << "Processing Accel Packet" << std::endl;
    Logging::insertAccelData(x, y, z);
    return;
}

