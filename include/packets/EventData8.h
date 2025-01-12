#ifndef EVENT_DATA8_H
#define EVENT_DATA8_H
#pragma once

#include "EventTypes.h"
#include "Packet.h"



// 10 bytes
class EventData8Packet : public Packet {                 // System packet
public:
    EventType event_type;
    uint8_t data;
    EventData8Packet(char hdr, EventType event_type, uint8_t data);
    void process() override;
};



#endif // EVENT_DATA8_H