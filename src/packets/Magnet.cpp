#include "packets/Magnet.h"
#include "Logging.h"
#include <stdint.h>

MagnetPacket::MagnetPacket(char hdr, int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z), Packet(PacketType::MAGNET, hdr) {}

void MagnetPacket::process() {
    //std::cout << "Processing Magnet Packet" << std::endl;
    Logging::insertMagData(x, y, z);
    return;
}
