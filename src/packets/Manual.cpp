#include "packets/Manual.h"
//#include <iostream>


ManualPacket::ManualPacket() : Packet(PacketType::MANUAL, 'm') {}

ManualPacket::ManualPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron) 
    : throttle(throttle), elevator(elevator), rudder(rudder), left_aileron(left_aileron), right_aileron(right_aileron), 
    Packet(PacketType::MANUAL, hdr) {}

void ManualPacket::process() {
    // Implement processing
    //std::cout << "Processing Manual Packet" << std::endl;
    return;
}

