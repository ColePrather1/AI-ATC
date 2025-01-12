#ifndef EVENT_DATA64_H
#define EVENT_DATA64_H
#pragma once
#include "Packet.h"
#include "EventTypes.h"


// 17 bytes
class EventData64Packet : public Packet {                 // System packet
public:
    EventType event_type;
    uint64_t data;
    EventData64Packet(char hdr, EventType event_type, uint64_t data);
    void process() override;

};

#endif // EVENT_DATA64_H