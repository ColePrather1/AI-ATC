#ifndef EVENT_H
#define EVENT_H

#pragma once

#include "EventTypes.h"
#include "Packet.h"

// 9 bytes
class EventPacket : public Packet {                 // System packet
public:
    EventType event_type;
    EventPacket(char hdr, EventType event_type);
    void process() override;
};


#endif // EVENT_H