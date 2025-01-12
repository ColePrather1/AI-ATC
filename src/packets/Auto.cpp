#include "packets/Auto.h"
#include "Logging.h"


AutoPacket::AutoPacket() : Packet(PacketType::AUTO, 'A') {}
AutoPacket::AutoPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron) : Packet(PacketType::AUTO, hdr) {}


void AutoPacket::process() {
    // TODO: implement
}