#include "packets/GPS_Env.h"
#include "Session.h"
#include "Logging.h"
#include <stdint.h>


GPSEnvPacket::GPSEnvPacket() : Packet(PacketType::GPS_ENV, 'G') {}
GPSEnvPacket::GPSEnvPacket(char hdr, uint16_t heading, uint16_t speed, uint8_t sats, uint8_t signal_strenght) : heading(heading), speed(speed), sats(sats), signal_strength(signal_strenght), Packet(PacketType::GPS_ENV, hdr) {}


void GPSEnvPacket::process() {
    //std::cout << "Processing GPS Env Packet" << std::endl;
    
    // 1) Store Pilot's current GPS Env data
    Session::airplane_current_gps_heading.store(heading);
    Session::airplane_current_gps_speed.store(speed);
    // 2) Send to SQL Logging 
    Logging::insertGPSEnvData(heading, speed, sats, signal_strength);       
    return;
}
