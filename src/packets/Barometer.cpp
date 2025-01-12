

#include "packets/Barometer.h"
#include "Logging.h"



BarometerPacket::BarometerPacket(int16_t pressure, int16_t temperature, int16_t baro_altitude) : pressure(pressure), temperature(temperature), baro_altitude(baro_altitude), Packet(PacketType::BAROMETER, 'b') {}


void BarometerPacket::process() {
    //std::cout << "Processing Barometer Packet" << std::endl;
    Logging::insertBaroData(pressure, temperature, baro_altitude);
    return;
}
