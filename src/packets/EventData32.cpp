#include "Session.h"
//#include "EventTypes.h"
#include "Logging.h"
#include "packets/EventData32.h"
#include <stdint.h>


EventData32Packet::EventData32Packet(char hdr, EventType event_type, uint32_t data) : event_type(event_type), data(data), Packet(PacketType::EVENT_DATA32, hdr) {}


void EventData32Packet::process() {
    switch (event_type) {


// TODO: Decode data for each
        case EventType::FIXED_HEADING_DATA_CHANGE:
            Session::fixed_plane_heading.store(data, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FIXED_HEADING_DATA_CHANGE, data);
            break;
// TODO: Decode data for each
        case EventType::FIXED_SPEED_DATA_CHANGE:
            Session::fixed_plane_speed.store(data, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FIXED_SPEED_DATA_CHANGE, data);
            break;

        default:
            break;
    }
    return;
}

