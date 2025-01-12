#ifndef EVENT_TIMED_DATA_H
#define EVENT_TIMED_DATA_H
#pragma once
#include "EventTypes.h"
#include "Packet.h"


// 17 bytes
class EventTimedDataPacket : public Packet {                 // System packet
public:
    EventType event_type;
    uint32_t timestamp;
    uint8_t data;
    EventTimedDataPacket(char hdr, EventType event_type, uint32_t timestamp, uint8_t data);
    void process() override;
};




#endif // EVENT_TIMED_DATA_H