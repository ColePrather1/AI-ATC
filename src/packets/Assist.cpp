#include "packets/Assist.h"
#include "Logging.h"


#include "packets/packets.h"
#include <cstdint>

AssistPacket::AssistPacket() : Packet(PacketType::ASSIST, 'a') {}

AssistPacket::AssistPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron) : Packet(PacketType::ASSIST, hdr) {}


void AssistPacket::process() {
    // TODO: implement
    return;
}