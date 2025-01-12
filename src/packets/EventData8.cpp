#include "packets/EventData8.h"
#include "Session.h"
#include "EventTypes.h"
#include "Logging.h"



EventData8Packet::EventData8Packet(char hdr, EventType event_type, uint8_t data) : event_type(event_type), data(data), Packet(PacketType::EVENT_DATA8, hdr) {}

void EventData8Packet::process(){
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
        case EventType::FIXED_SPEED_DATA_CHANGE:
            Session::fixed_plane_speed.store(data, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FIXED_SPEED_DATA_CHANGE, data);
            break;
        default:
            break;
    }
    return;
}


