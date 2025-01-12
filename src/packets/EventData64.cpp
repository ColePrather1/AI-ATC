#include "packets/EventData64.h"
#include "Session.h"
//#include "EventTypes.h"
#include "Logging.h"
#include <stdint.h>


EventData64Packet::EventData64Packet(char hdr, EventType event_type, uint64_t data) : data(data), event_type(event_type), Packet(PacketType::EVENT_DATA64, hdr) {}

void EventData64Packet::process() {
    switch (event_type) {


// TODO: Decode data for each
        case EventType::THROTTLE_LOCK_DATA_CHANGE:
            Session::throttle_lock_val.store(data, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::THROTTLE_LOCK_DATA_CHANGE, data);
            break;
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

// TODO: Decode data waypoint
        case EventType::WAYPOINT_DATA_UPDATE:
            Logging::insertEventLog(EventType::WAYPOINT_DATA_UPDATE, data);
            //Session::waypoint_lat.store(data >> 32, std::memory_order_relaxed);
            //Session::waypoint_lon.store(data, std::memory_order_relaxed);
            //Session::waypoint_alt.store(data, std::memory_order_relaxed);
            break;
        default:
            break;
    }
    return;
}

