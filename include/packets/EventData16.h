#ifndef EVENT_DATA16_H
#define EVENT_DATA16_H

#pragma once

//#include "Session.h"
#include "EventTypes.h"
//#include "Logging.h"
#include "Packet.h"
//#include <chrono>


//#include "../src/EventTypes.h"





// 11 bytes
class EventData16Packet : public Packet {                 // System packet
public:
    EventType event_type;
    uint16_t data;
    EventData16Packet(char hdr, EventType event_type, uint16_t data);
    void process() override;

};



#endif // EVENT_DATA16_H