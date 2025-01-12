#ifndef EVENT_DATA32_H
#define EVENT_DATA32_H
#pragma once
#include "Packet.h"
#include "EventTypes.h"


// 13 bytes
class EventData32Packet : public Packet {                 // System packet
public:
    EventType event_type;
    uint32_t data;
    EventData32Packet(char hdr, EventType event_type, uint32_t data);
    void process() override;

};


#endif // EVENT_DATA32_H