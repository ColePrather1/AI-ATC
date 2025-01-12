#include "packets/EventTimed.h"
#include "Session.h"
#include "Logging.h"



//#include <chrono>


EventTimedPacket::EventTimedPacket(char hdr, EventType event_type, uint32_t timestamp) : event_type(event_type), timestamp(timestamp), Packet(PacketType::EVENT_TIMED, hdr) {}


void EventTimedPacket::process() {
    switch (event_type) {
        // System Events
        case EventType::SYSTEM_STARTUP: 
            //Logging::insertEventLog(EventType::SYSTEM_STARTUP, timestamp);
            Logging::insertEventLog(EventType::SYSTEM_STARTUP, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::SYSTEM_STARTUP, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::SYSTEM_SHUTDOWN:
            Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::SYSTEM_RESTART:
            Logging::insertEventLog(EventType::SYSTEM_RESTART, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::SYSTEM_RESTART, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::KILL_PILOT:
            Logging::insertEventLog(EventType::KILL_PILOT, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::KILL_PILOT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;

        case EventType::FLIGHT_TIME_START_SET_TRUE:
            Session::flight_time_start.store(timestamp, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FLIGHT_TIME_START_SET_TRUE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_TIME_START_SET_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::FLIGHT_TIME_START_SET_FALSE:
            Session::flight_time_start.store(0, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FLIGHT_TIME_START_SET_FALSE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_TIME_START_SET_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;    
        case EventType::FLIGHT_TIME_END_SET_TRUE:
            Session::flight_time_end.store(timestamp, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FLIGHT_TIME_END_SET_TRUE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_TIME_END_SET_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::FLIGHT_TIME_END_SET_FALSE:
            Session::flight_time_end.store(0, std::memory_order_relaxed);
            Logging::insertEventLog(EventType::FLIGHT_TIME_END_SET_FALSE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_TIME_END_SET_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::FLIGHT_START_TRUE:
            Logging::insertEventLog(EventType::FLIGHT_START_TRUE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_START_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;
        case EventType::FLIGHT_START_FALSE:
            Logging::insertEventLog(EventType::FLIGHT_START_FALSE, EVENT_LOG_NULL_DATA, timestamp);
            //Logging::insertEventLog(EventType::FLIGHT_START_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
            break;

        // Control Mode Events                      // To plane only
        //case EventType::CONTROL_MODE_CHANGE_AUTO:
        //case EventType::CONTROL_MODE_CHANGE_ASSIST:
        //case EventType::CONTROL_MODE_CHANGE_MANUAL:
        //case EventType::CONTROL_MODE_CHANGE_HOLDING:
        //case EventType::CONTROL_MODE_CHANGE_TAXI:
        //case EventType::CONTROL_MODE_CHANGE_EMERGENCY:
        //case EventType::CONTROL_MODE_CHANGE_RECOVERY:
        //case EventType::CONTROL_MODE_CHANGE_PAIRING:

        //case EventType::CONTROL_MODE_CHANGE_AUTO_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_AUTO_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;           
        //case EventType::CONTROL_MODE_CHANGE_ASSIST_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_ASSIST_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;           
        //case EventType::CONTROL_MODE_CHANGE_MANUAL_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_MANUAL_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   
        //case EventType::CONTROL_MODE_CHANGE_HOLDING_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_HOLDING_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   
        //case EventType::CONTROL_MODE_CHANGE_TAXI_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_TAXI_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   
        //case EventType::CONTROL_MODE_CHANGE_EMERGENCY_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_EMERGENCY_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   
        //case EventType::CONTROL_MODE_CHANGE_RECOVERY_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_RECOVERY_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   
        //case EventType::CONTROL_MODE_CHANGE_PAIRING_ACCEPT:
        //    Session::insertEventLog(EventType::CONTROL_MODE_CHANGE_PAIRING_ACCEPT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;   

        // Airplane Status Events                           // EventPacket
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
        ////case EventType::FIXED_ALTITUDE_DATA_CHANGE:
        //case EventType::FIXED_ALTITUDE_FALSE:
        //case EventType::FIXED_ALTITUDE_TRUE:
        ////case EventType::FIXED_HEADING_DATA_CHANGE:
        //case EventType::FIXED_HEADING_FALSE:
        //case EventType::FIXED_HEADING_TRUE:
        ////case EventType::FIXED_SPEED_DATA_CHANGE:
        //case EventType::FIXED_SPEED_FALSE:
        //case EventType::FIXED_SPEED_TRUE:
        //    logEvent(std::string("Event: ") + std::to_string(static_cast<int>(event)));
        //    break;

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
        //case EventType::WAYPOINT_DATA_UPDATE:
        //    break;

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
            //logEvent("Unknown event: " + std::to_string(static_cast<int>(event)));
            break;
    }
    return;
}

