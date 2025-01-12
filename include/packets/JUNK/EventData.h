#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#pragma once

//#include "../src/Common.h"
#include "../src/Session.h"

#include "Packet.h"

//#include "Bitmask.h"

#include "../src/EventTypes.h"

//#include "../src/EventActions.h"

#include "../src/Logging.h"

#include <chrono>


#include "../src/EventTypes.h"







// 17 bytes
class EventDataPacket : public Packet {                 // System packet
private:
    EventDataPacket() = default;
    ~EventDataPacket() = default;
public:
    EventType event_type;
    //std::byte data[8];
    uint64_t data;
    bool process() override;


    uint32_t data_size;
    uint8_t data[];  // Flexible array member

    static EventDataPacket* create(EventType type, const void* data, uint32_t size) {
        void* memory = ::operator new(sizeof(EventDataPacket) + size);
        EventDataPacket* packet = new(memory) EventDataPacket();
        packet->event_type = type;
        packet->data_size = size;
        std::memcpy(packet->data, data, size);
        return packet;
    }

    static void destroy(EventDataPacket* packet) {
        packet->~EventDataPacket();
        ::operator delete(packet);
    }


};

void EventDataPacket::process() {
    switch (event_type) {


        // Airplane Status Events
        //case EventType::AIRPLANE_CONNECTED_TRUE:
        //case EventType::AIRPLANE_CONNECTED_FALSE:
        //case EventType::PAIRED_FALSE:
        //case EventType::PAIRED_TRUE:
        //case EventType::PAIRED_DISCONNECTED:
        //case EventType::THROTTLE_LOCK_FALSE:
        //case EventType::THROTTLE_LOCK_TRUE:
        //case EventType::WITHIN_RANGE_FALSE:
        //case EventType::WITHIN_RANGE_TRUE:
        //case EventType::APPROACHING_BOUNDARY_FALSE:
        //case EventType::APPROACHING_BOUNDARY_TRUE:
        //case EventType::RETURNING_HOME_FALSE:
        //case EventType::RETURNING_HOME_TRUE:
        //case EventType::FLYING_FALSE:
        //case EventType::FLYING_TRUE:
        //case EventType::GPS_ACTIVE_FALSE:
        //case EventType::GPS_ACTIVE_TRUE:
        //case EventType::GPS_FAIL:
        //case EventType::IMU_ACTIVE_FALSE:
        //case EventType::IMU_ACTIVE_TRUE:
        //case EventType::IMU_FAIL:

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

        // Airplane Events
        //case EventType::ENGINE_ON_TRUE:
        //case EventType::ENGINE_ON_FALSE:
        //    logEvent(std::string("Engine event: ") + std::to_string(static_cast<int>(event)));
        //    break;

        // Flight Events
        //case EventType::ALTITUDE_OK:
        //case EventType::ALTITUDE_WARNING:
        //case EventType::ALTITUDE_LOW:
        //case EventType::ALTITUDE_HIGH:
        //case EventType::PITCH_OK:
        //case EventType::PITCH_WARNING:
        //case EventType::PITCH_LOW:
        //case EventType::PITCH_HIGH:
        //case EventType::ROLL_OK:
        //case EventType::ROLL_LEFT_LOW:
        //case EventType::ROLL_LEFT_MID:
        //case EventType::ROLL_LEFT_HIGH:
        //case EventType::ROLL_LEFT_WARNING:
        //case EventType::ROLL_LEFT_DANGER:
        //case EventType::ROLL_RIGHT_LOW:
        //case EventType::ROLL_RIGHT_MID:
        //case EventType::ROLL_RIGHT_HIGH:
        //case EventType::ROLL_RIGHT_WARNING:
        //case EventType::ROLL_RIGHT_DANGER:
        //case EventType::SPEED_OK:
        //case EventType::SPEED_LOW:
        //case EventType::SPEED_HIGH:
        //case EventType::ENGINE_STALL_FALSE:
        //case EventType::ENGINE_STALL_TRUE:
        //case EventType::MOTOR_SPINNING_TRUE:
        //case EventType::MOTOR_SPINNING_FALSE:
        //    logEvent(std::string("Flight event: ") + std::to_string(static_cast<int>(event)));
        //    break;

        // Flight Plan Events
        //case EventType::WAYPOINT_SET_FALSE:
        //case EventType::WAYPOINT_SET_TRUE:
// TODO: Decode data waypoint
        case EventType::WAYPOINT_DATA_UPDATE:
            Logging::insertEventLog(EventType::WAYPOINT_DATA_UPDATE, data);
            Session::waypoint_data.store(data, std::memory_order_relaxed);
            break;

        // Flight Phase Events
        //case EventType::FLIGHT_PHASE_CHANGE_NONE:
        //case EventType::FLIGHT_PHASE_CHANGE_INIT:
        //case EventType::FLIGHT_PHASE_CHANGE_TAXI_TO_TAKEOFF:
        //case EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_PREP:
        //case EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ROLL:
        //case EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ASCEND:
        //case EventType::FLIGHT_PHASE_CHANGE_CLIMB:
        //case EventType::FLIGHT_PHASE_CHANGE_CRUISE:
        //case EventType::FLIGHT_PHASE_CHANGE_DESCENT:
        //case EventType::FLIGHT_PHASE_CHANGE_ALIGN_APPROACH:
        //case EventType::FLIGHT_PHASE_CHANGE_FINAL_APPROACH:
        //case EventType::FLIGHT_PHASE_CHANGE_FLARE:
        //case EventType::FLIGHT_PHASE_CHANGE_TOUCHDOWN:
        //case EventType::FLIGHT_PHASE_CHANGE_ROLL_OUT:
        //case EventType::FLIGHT_PHASE_CHANGE_GO_AROUND:
        //case EventType::FLIGHT_PHASE_CHANGE_HOLDING_PATTERN:
        //case EventType::FLIGHT_PHASE_CHANGE_EMERGENCY_LANDING:
        //case EventType::FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT:
        //    logEvent(std::string("Flight phase change: ") + std::to_string(static_cast<int>(event)));
        //    break;

        default:
            break;
    }
}



#endif // EVENT_DATA_H