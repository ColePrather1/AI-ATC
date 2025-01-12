#ifndef EVENT_TIMED_H
#define EVENT_TIMED_H
#pragma once
#include "EventTypes.h"
#include "Packet.h"


// 17 bytes
class EventTimedPacket : public Packet {                 // System packet
public:
    EventType event_type;
    uint32_t timestamp;
    EventTimedPacket (char hdr, EventType event_type, uint32_t timestamp);
    void process() override;
};


#endif // EVENT_TIMED_H