#include "packets/Temp-Humid.h"
#include <stdint.h>
//#include "Logging.h"
//#include "Session.h"


TempHumidPacket::TempHumidPacket(char hdr, uint16_t temp, uint16_t humid) : temp(temp), humid(humid), Packet(PacketType::TEMP_HUMID, hdr) {}


void TempHumidPacket::process() {
    //std::cout << "Processing Accel Packet" << std::endl;
    //Logging::insertTempHumidData(temp, humid);
    return;
}
