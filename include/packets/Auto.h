#ifndef AUTO_H
#define AUTO_H
#pragma once
#include "Packet.h"


class AutoPacket : public Packet {
public:
    uint8_t throttle;
    uint8_t elevator;
    uint8_t rudder;
    uint8_t left_aileron;
    uint8_t right_aileron;

    AutoPacket();
    AutoPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    void process() override;
};

#endif // AUTO_H

