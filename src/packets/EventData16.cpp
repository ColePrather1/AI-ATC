#include "packets/EventData16.h"
#include "Session.h"
#include "Logging.h"




EventData16Packet::EventData16Packet(char hdr, EventType event_type, uint16_t data) : event_type(event_type), data(data), Packet(PacketType::EVENT_DATA16, hdr) {}


void EventData16Packet::process() {
    switch (event_type) {


// TODO: Decode data for each
        case EventType::FIXED_ALTITUDE_DATA_CHANGE:
            Session::fixed_plane_altitude.store(data, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FIXED_ALTITUDE_DATA_CHANGE, data);
            break;
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
