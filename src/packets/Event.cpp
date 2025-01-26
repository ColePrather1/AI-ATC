
#include "Session.h"
#include "EventTypes.h"
#include "Logging.h"
#include "packets/Event.h"

#include <chrono>

#include <cstdint>


//#include "Bitmask.h"

//#include "../src/EventTypes.h"
//#include "../include/EventTypes.h"

//#include "../src/EventActions.h"

//#include "../src/Logging.h"
//#include "../include/Logging.h"


EventPacket::EventPacket(char hdr, EventType event_type) : Packet(PacketType::EVENT, hdr) {
    this->event_type = event_type;
    payload.push_back(static_cast<uint8_t>(event_type));
    payload.shrink_to_fit();
    payload[2] = static_cast<uint8_t>(payload.size());
}


void EventPacket::process(){
    switch (event_type) {
        // System Events
        //case EventType::SYSTEM_STARTUP: 
        //    Logging::insertEventLog(EventType::SYSTEM_STARTUP, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        //    break;
        //case EventType::SYSTEM_SHUTDOWN:
        //    Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        //    break;
        //case EventType::SYSTEM_RESTART:
        //    Logging::insertEventLog(EventType::SYSTEM_RESTART, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        //    break;
        //case EventType::KILL_PILOT:
        //    Logging::insertEventLog(EventType::KILL_PILOT, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        //    break;
        //
        //case EventType::FLIGHT_TIME_START_SET_TRUE:
        //    Session::insertEventLog(EventType::FLIGHT_TIME_START_SET_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;
        //case EventType::FLIGHT_TIME_START_SET_FALSE:
        //    Session::insertEventLog(EventType::FLIGHT_TIME_START_SET_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;    
        //case EventType::FLIGHT_TIME_END_SET_TRUE:
        //    Session::insertEventLog(EventType::FLIGHT_TIME_END_SET_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;
        //case EventType::FLIGHT_TIME_END_SET_FALSE:
        //    Session::insertEventLog(EventType::FLIGHT_TIME_END_SET_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;
        //case EventType::FLIGHT_START_TRUE:
        //    Session::insertEventLog(EventType::FLIGHT_START_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;
        //case EventType::FLIGHT_START_FALSE:
        //    Session::insertEventLog(EventType::FLIGHT_START_FALSE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), static_cast<uint64_t>(0));
        //    break;

        // Control Mode Events                      // To plane only
        //case EventType::CONTROL_MODE_CHANGE_AUTO:
        //case EventType::CONTROL_MODE_CHANGE_ASSIST:
        //case EventType::CONTROL_MODE_CHANGE_MANUAL:
        //case EventType::CONTROL_MODE_CHANGE_HOLDING:
        //case EventType::CONTROL_MODE_CHANGE_TAXI:
        //case EventType::CONTROL_MODE_CHANGE_EMERGENCY:
        //case EventType::CONTROL_MODE_CHANGE_RECOVERY:
        //case EventType::CONTROL_MODE_CHANGE_PAIRING:

        case EventType::CONTROL_MODE_CHANGE_AUTO_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_AUTO_ACCEPT);
            break;           
        case EventType::CONTROL_MODE_CHANGE_ASSIST_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_ASSIST_ACCEPT);
            break;           
        case EventType::CONTROL_MODE_CHANGE_MANUAL_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_MANUAL_ACCEPT);
            break;   
        case EventType::CONTROL_MODE_CHANGE_HOLDING_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_HOLDING_ACCEPT);
            break;   
        case EventType::CONTROL_MODE_CHANGE_TAXI_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_TAXI_ACCEPT);
            break;   
        case EventType::CONTROL_MODE_CHANGE_EMERGENCY_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_EMERGENCY_ACCEPT);
            break;   
        case EventType::CONTROL_MODE_CHANGE_RECOVERY_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_RECOVERY_ACCEPT);
        case EventType::CONTROL_MODE_CHANGE_PAIRING_ACCEPT:
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_PAIRING_ACCEPT);
            break;   

        // Airplane Status Events                           // EventPacket
        //case EventType::AIRPLANE_CONNECTED_TRUE:      // PAIRED is used instead
        //case EventType::AIRPLANE_CONNECTED_FALSE:
        case EventType::PAIRED_FALSE:
            Session::paired.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::PAIRED_FALSE);
            break;
        case EventType::PAIRED_TRUE:
            Session::paired.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::PAIRED_TRUE);
            break;
        case EventType::PAIRED_FAIL:    // TODO: Implement reconnect logic function call
            Session::paired.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::PAIRED_FAIL);
            break;
        case EventType::THROTTLE_LOCK_FALSE:
            Session::throttle_lock.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::THROTTLE_LOCK_FALSE);
            break;
        case EventType::THROTTLE_LOCK_TRUE:
            Session::throttle_lock.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::THROTTLE_LOCK_TRUE);
            break;
        case EventType::WITHIN_RANGE_FALSE:
            Session::within_range.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::WITHIN_RANGE_FALSE);
            break;
        case EventType::WITHIN_RANGE_TRUE:
            Session::within_range.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::WITHIN_RANGE_TRUE);
            break;
        case EventType::APPROACHING_BOUNDARY_FALSE:
            Session::approaching_boundary.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::APPROACHING_BOUNDARY_FALSE);
            break;
        case EventType::APPROACHING_BOUNDARY_TRUE:  // TODO: Implement logic
            Session::approaching_boundary.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::APPROACHING_BOUNDARY_TRUE);
            break;
        case EventType::RETURNING_HOME_FALSE:
            Session::returning_home.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::RETURNING_HOME_FALSE);
            break;
        case EventType::RETURNING_HOME_TRUE:
            Session::returning_home.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::RETURNING_HOME_TRUE);
            break;
        case EventType::IS_FLYING_FALSE:   // TODO: Implement logic
            Session::isFlying.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::IS_FLYING_FALSE);
            break;
        case EventType::IS_FLYING_TRUE:
            Session::isFlying.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::IS_FLYING_TRUE);
            break;
        case EventType::AIRPLANE_GPS_ACTIVE_FALSE:
            Session::airplane_gps_active.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::AIRPLANE_GPS_ACTIVE_FALSE);
            break;
        case EventType::AIRPLANE_GPS_ACTIVE_TRUE:
            Session::airplane_gps_active.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::AIRPLANE_GPS_ACTIVE_TRUE);
            break;
        case EventType::AIRPLANE_GPS_FAIL_FALSE:    // TODO: Implement logic
            Session::airplane_gps_fail.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::AIRPLANE_GPS_FAIL_FALSE);
            break;
        case EventType::AIRPLANE_GPS_FAIL_TRUE:
            Session::airplane_gps_fail.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::AIRPLANE_GPS_FAIL_TRUE);
            break;
        case EventType::ATC_GPS_ACTIVE_FALSE:
            Session::atc_gps_active.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::ATC_GPS_ACTIVE_FALSE);
            break;
        case EventType::ATC_GPS_ACTIVE_TRUE:    
            Session::atc_gps_active.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::ATC_GPS_ACTIVE_TRUE);
            break;
        case EventType::ATC_GPS_FAIL_FALSE:
            Session::atc_gps_fail.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::ATC_GPS_FAIL_FALSE);
            break;
        case EventType::ATC_GPS_FAIL_TRUE:
            Session::atc_gps_fail.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::ATC_GPS_FAIL_TRUE);
            break;
        case EventType::IMU_ACTIVE_FALSE:
            Session::imu_active.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::IMU_ACTIVE_FALSE);
            break;
        case EventType::IMU_ACTIVE_TRUE:
            Session::imu_active.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::IMU_ACTIVE_TRUE);
            break;
        case EventType::IMU_FAIL_FALSE:
            Session::imu_fail.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::IMU_FAIL_FALSE);
            break;
        case EventType::IMU_FAIL_TRUE:
            Session::imu_fail.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::IMU_FAIL_TRUE);
            break;
        //case EventType::FIXED_ALTITUDE_DATA_CHANGE:
        case EventType::FIXED_ALTITUDE_FALSE:
            Session::fixed_altitude.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_ALTITUDE_FALSE);
            break;
        case EventType::FIXED_ALTITUDE_TRUE:
            Session::fixed_altitude.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_ALTITUDE_TRUE);
            break;
        //case EventType::FIXED_HEADING_DATA_CHANGE:
        case EventType::FIXED_HEADING_FALSE:
            Session::fixed_heading.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_HEADING_FALSE);
            break;
        case EventType::FIXED_HEADING_TRUE:
            Session::fixed_heading.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_HEADING_TRUE);
            break;
        //case EventType::FIXED_SPEED_DATA_CHANGE:
        case EventType::FIXED_SPEED_FALSE:
            Session::fixed_speed.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_SPEED_FALSE);
            break;
        case EventType::FIXED_SPEED_TRUE:
            Session::fixed_speed.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::FIXED_SPEED_TRUE);
            break;

        // Airplane Events
        case EventType::ENGINE_ON_TRUE:
            Session::engine_active.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_ON_TRUE);
            break;
        case EventType::ENGINE_ON_FALSE:
            Session::engine_active.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_ON_FALSE);
            break;
        case EventType::ENGINE_FAIL_FALSE:
            Session::engine_fail.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_FAIL_FALSE);
            break;
        case EventType::ENGINE_FAIL_TRUE:
            Session::engine_fail.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_FAIL_TRUE);
            break;


        // Flight Events
        case EventType::ALTITUDE_GROUND:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(0), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_GROUND);
            break;
        case EventType::ALTITUDE_OK:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(1), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_OK);
            break;
        case EventType::ALTITUDE_WARNING_LOW:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(2), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_WARNING_LOW);
            break;
        case EventType::ALTITUDE_LOW:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(3), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_LOW);
            break;
        case EventType::ALTITUDE_HIGH:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(4), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_HIGH);
            break;
        case EventType::ALTITUDE_WARNING_HIGH:
            Session::plane_altitude_level.store(static_cast<TypeLevel>(5), std::memory_order_release);
            Logging::insertEventLog(EventType::ALTITUDE_WARNING_HIGH);
            break;

        case EventType::PITCH_GROUND:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(0), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_GROUND);
            break;
        case EventType::PITCH_OK:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(1), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_OK);
            break;
        case EventType::PITCH_WARNING_LOW:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(2), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_WARNING_LOW);
            break;
        case EventType::PITCH_LOW:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(3), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_LOW);
            break;
        case EventType::PITCH_HIGH:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(4), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_HIGH);
            break;
        case EventType::PITCH_WARNING_HIGH:
            Session::plane_pitch_level.store(static_cast<TypeLevel>(5), std::memory_order_release);
            Logging::insertEventLog(EventType::PITCH_WARNING_HIGH);
            break;
        
        case EventType::ROLL_OK:
            Session::plane_roll_level.store(static_cast<RollLevel>(0), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_OK);
            break;
        case EventType::ROLL_LEFT_LOW:
            Session::plane_roll_level.store(static_cast<RollLevel>(1), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_LEFT_LOW);
            break;
        case EventType::ROLL_LEFT_MID:
            Session::plane_roll_level.store(static_cast<RollLevel>(2), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_LEFT_MID);
            break;
        case EventType::ROLL_LEFT_HIGH:
            Session::plane_roll_level.store(static_cast<RollLevel>(3), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_LEFT_HIGH);
            break;
        case EventType::ROLL_LEFT_WARNING:
            Session::plane_roll_level.store(static_cast<RollLevel>(4), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_LEFT_WARNING);
            break;
        case EventType::ROLL_LEFT_DANGER:
            Session::plane_roll_level.store(static_cast<RollLevel>(5), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_LEFT_DANGER);
            break;
        case EventType::ROLL_RIGHT_LOW:
            Session::plane_roll_level.store(static_cast<RollLevel>(6), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_RIGHT_LOW);
            break;
        case EventType::ROLL_RIGHT_MID:
            Session::plane_roll_level.store(static_cast<RollLevel>(7), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_RIGHT_MID);
            break;
        case EventType::ROLL_RIGHT_HIGH:
            Session::plane_roll_level.store(static_cast<RollLevel>(8), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_RIGHT_HIGH);
            break;
        case EventType::ROLL_RIGHT_WARNING:
            Session::plane_roll_level.store(static_cast<RollLevel>(9), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_RIGHT_WARNING);
            break;
        case EventType::ROLL_RIGHT_DANGER:
            Session::plane_roll_level.store(static_cast<RollLevel>(10), std::memory_order_release);
            Logging::insertEventLog(EventType::ROLL_RIGHT_DANGER);
            break;

        
        case EventType::AIR_SPEED_GROUND:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(0), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_GROUND);
            break;
        case EventType::AIR_SPEED_OK:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(1), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_OK);
            break;
        case EventType::AIR_SPEED_WARNING_LOW:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(2), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_WARNING_LOW);
            break;
        case EventType::AIR_SPEED_LOW:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(3), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_LOW);
            break;
        case EventType::AIR_SPEED_HIGH:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(4), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_HIGH);
            break;
        case EventType::AIR_SPEED_WARNING_HIGH:
            Session::plane_air_speed_level.store(static_cast<TypeLevel>(5), std::memory_order_release);
            Logging::insertEventLog(EventType::AIR_SPEED_WARNING_HIGH);
            break;

        
        case EventType::ENGINE_STALL_FALSE:
            Session::engine_stall.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_STALL_FALSE);
            break;
        case EventType::ENGINE_STALL_TRUE:
            Session::engine_stall.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::ENGINE_STALL_TRUE);
            break;
        case EventType::MOTOR_SPINNING_TRUE:
            Session::isMotorSpinning.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::MOTOR_SPINNING_TRUE);
            break;
        case EventType::MOTOR_SPINNING_FALSE:
            Session::isMotorSpinning.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::MOTOR_SPINNING_FALSE);
            break;

        // Flight Plan Events
        case EventType::WAYPOINT_SET_FALSE:
            Session::isWaypointSet.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::WAYPOINT_SET_FALSE);
            break;
        case EventType::WAYPOINT_SET_TRUE:
            Session::isWaypointSet.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::WAYPOINT_SET_TRUE);
            break;
        case EventType::WAYPOINT_ENROUTE_TRUE:
            Session::isEnrouteToWaypoint.store(true, std::memory_order_release);
            Logging::insertEventLog(EventType::WAYPOINT_ENROUTE_TRUE);
            break;
        case EventType::WAYPOINT_ENROUTE_FALSE:
            Session::isEnrouteToWaypoint.store(false, std::memory_order_release);
            Logging::insertEventLog(EventType::WAYPOINT_ENROUTE_FALSE);
            break;
        //case EventType::WAYPOINT_DATA_UPDATE:

        // Flight Phase Events
        case EventType::FLIGHT_PHASE_CHANGE_NONE:
            Session::airplane_active_flight_phase.store(FlightPhase::NONE, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_NONE);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_INIT:
            Session::airplane_active_flight_phase.store(FlightPhase::INIT, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_INIT);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_TAXI_TO_RUNWAY:
            Session::airplane_active_flight_phase.store(FlightPhase::TAXI_TO_RUNWAY, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_TAXI_TO_RUNWAY);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_PREFLIGHT_CHECKS:
            Session::airplane_active_flight_phase.store(FlightPhase::PREFLIGHT_CHECKS, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_PREFLIGHT_CHECKS);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ROLL:
            Session::airplane_active_flight_phase.store(FlightPhase::TAKEOFF_ROLL, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ROLL);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ASCEND:
            Session::airplane_active_flight_phase.store(FlightPhase::TAKEOFF_ASCEND, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ASCEND);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_CLIMB:
            Session::airplane_active_flight_phase.store(FlightPhase::CLIMB, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_CLIMB);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_CRUISE:
            Session::airplane_active_flight_phase.store(FlightPhase::CRUISE, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_CRUISE);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_DESCENT:
            Session::airplane_active_flight_phase.store(FlightPhase::DESCENT, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_DESCENT);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_ALIGN_APPROACH:
            Session::airplane_active_flight_phase.store(FlightPhase::ALIGN_APPROACH, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_ALIGN_APPROACH);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_FINAL_APPROACH:
            Session::airplane_active_flight_phase.store(FlightPhase::FINAL_APPROACH, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_FINAL_APPROACH);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_FLARE:
            Session::airplane_active_flight_phase.store(FlightPhase::FLARE, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_FLARE);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_TOUCHDOWN:
            Session::airplane_active_flight_phase.store(FlightPhase::TOUCHDOWN, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_TOUCHDOWN);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_ROLL_OUT:
            Session::airplane_active_flight_phase.store(FlightPhase::ROLL_OUT, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_ROLL_OUT);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_GO_AROUND:
            Session::airplane_active_flight_phase.store(FlightPhase::GO_AROUND, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_GO_AROUND);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_HOLDING_PATTERN:
            Session::airplane_active_flight_phase.store(FlightPhase::HOLDING_PATTERN, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_HOLDING_PATTERN);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_EMERGENCY_LANDING:
            Session::airplane_active_flight_phase.store(FlightPhase::EMERGENCY_LANDING, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_EMERGENCY_LANDING);
            break;
        case EventType::FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT:
            Session::airplane_active_flight_phase.store(FlightPhase::COMPLETE_FLIGHT, std::memory_order_release);
            Logging::insertEventLog(EventType::FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT);
            break;
        default:
            break;
    }
    return;
}

