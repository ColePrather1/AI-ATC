#ifndef ASSIST_H
#define ASSIST_H
#pragma once

#include "Packet.h"

#include <cstdint>

class AssistPacket : public Packet {
public:
    uint8_t throttle;
    uint8_t elevator;
    uint8_t rudder;
    uint8_t left_aileron;
    uint8_t right_aileron;

    AssistPacket();
    AssistPacket(char hdr, uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    void process() override;
};

#endif // ASSIST_H