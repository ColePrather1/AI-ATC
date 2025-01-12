#ifndef EVENT_ACTIONS_H
#define EVENT_ACTIONS_H

#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <chrono>
#include "EventTypes.h"
#include "Logging.h"
#include "Common.h"
#include "Session.h"

class EventActions {
private:
    using EventHandler = std::function<void()>;
    std::array<EventHandler, static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT) + 1> handlers;

    void logEvent(const std::string& eventName) {
        std::cout << "Event occurred: " << eventName << std::endl;
    }

public:
    EventActions() {
        initializeHandlers();
    }

    void handleEvent(EventType event) {
        if (static_cast<size_t>(event) < handlers.size()) {
            handlers[static_cast<size_t>(event)]();
        }
    }

private:
    void initializeHandlers() {
        // System Events
        handlers[static_cast<size_t>(EventType::SYSTEM_STARTUP)] = [this]() { 
            Logging::insertEventLog(EventType::SYSTEM_STARTUP, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        };
        handlers[static_cast<size_t>(EventType::SYSTEM_SHUTDOWN)] = [this]() { 
            Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        };
        handlers[static_cast<size_t>(EventType::SYSTEM_RESTART)] = [this]() { 
            Logging::insertEventLog(EventType::SYSTEM_RESTART, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        };
        handlers[static_cast<size_t>(EventType::KILL_PILOT)] = [this]() { logEvent("KILL_PILOT"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_TIME_START_SET_TRUE)] = [this]() {
            Session::insertEventLog(EventType::FLIGHT_TIME_START_SET_TRUE, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()), 0);
        };
        handlers[static_cast<size_t>(EventType::FLIGHT_TIME_START_SET_FALSE)] = [this]() { logEvent("FLIGHT_TIME_START_SET_FALSE"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_TIME_END_SET_TRUE)] = [this]() { logEvent("FLIGHT_TIME_END_SET_TRUE"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_TIME_END_SET_FALSE)] = [this]() { logEvent("FLIGHT_TIME_END_SET_FALSE"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_START_TRUE)] = [this]() { logEvent("FLIGHT_START_TRUE"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_START_FALSE)] = [this]() { logEvent("FLIGHT_START_FALSE"); };

        // Control Mode Events
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_AUTO)] = [this]() { logEvent("CONTROL_MODE_CHANGE_AUTO"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_ASSIST)] = [this]() { logEvent("CONTROL_MODE_CHANGE_ASSIST"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_MANUAL)] = [this]() { logEvent("CONTROL_MODE_CHANGE_MANUAL"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_HOLDING)] = [this]() { logEvent("CONTROL_MODE_CHANGE_HOLDING"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_TAXI)] = [this]() { logEvent("CONTROL_MODE_CHANGE_TAXI"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_EMERGENCY)] = [this]() { logEvent("CONTROL_MODE_CHANGE_EMERGENCY"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_RECOVERY)] = [this]() { logEvent("CONTROL_MODE_CHANGE_RECOVERY"); };
        handlers[static_cast<size_t>(EventType::CONTROL_MODE_CHANGE_PAIRING)] = [this]() { logEvent("CONTROL_MODE_CHANGE_PAIRING"); };

        // Airplane Status Events
        handlers[static_cast<size_t>(EventType::AIRPLANE_CONNECTED_TRUE)] = [this]() { logEvent("AIRPLANE_CONNECTED_TRUE"); };
        handlers[static_cast<size_t>(EventType::AIRPLANE_CONNECTED_FALSE)] = [this]() { logEvent("AIRPLANE_CONNECTED_FALSE"); };
        handlers[static_cast<size_t>(EventType::PAIRED_FALSE)] = [this]() { logEvent("PAIRED_FALSE"); };
        handlers[static_cast<size_t>(EventType::PAIRED_TRUE)] = [this]() { logEvent("PAIRED_TRUE"); };
        handlers[static_cast<size_t>(EventType::PAIRED_DISCONNECTED)] = [this]() { logEvent("PAIRED_DISCONNECTED"); };
        handlers[static_cast<size_t>(EventType::THROTTLE_LOCK_FALSE)] = [this]() { logEvent("THROTTLE_LOCK_FALSE"); };
        handlers[static_cast<size_t>(EventType::THROTTLE_LOCK_TRUE)] = [this]() { logEvent("THROTTLE_LOCK_TRUE"); };
        handlers[static_cast<size_t>(EventType::WITHIN_RANGE_FALSE)] = [this]() { logEvent("WITHIN_RANGE_FALSE"); };
        handlers[static_cast<size_t>(EventType::WITHIN_RANGE_TRUE)] = [this]() { logEvent("WITHIN_RANGE_TRUE"); };
        handlers[static_cast<size_t>(EventType::APPROACHING_BOUNDARY_FALSE)] = [this]() { logEvent("APPROACHING_BOUNDARY_FALSE"); };
        handlers[static_cast<size_t>(EventType::APPROACHING_BOUNDARY_TRUE)] = [this]() { logEvent("APPROACHING_BOUNDARY_TRUE"); };
        handlers[static_cast<size_t>(EventType::RETURNING_HOME_FALSE)] = [this]() { logEvent("RETURNING_HOME_FALSE"); };
        handlers[static_cast<size_t>(EventType::RETURNING_HOME_TRUE)] = [this]() { logEvent("RETURNING_HOME_TRUE"); };
        handlers[static_cast<size_t>(EventType::FLYING_FALSE)] = [this]() { logEvent("FLYING_FALSE"); };
        handlers[static_cast<size_t>(EventType::FLYING_TRUE)] = [this]() { logEvent("FLYING_TRUE"); };
        handlers[static_cast<size_t>(EventType::GPS_ACTIVE_FALSE)] = [this]() { logEvent("GPS_ACTIVE_FALSE"); };
        handlers[static_cast<size_t>(EventType::GPS_ACTIVE_TRUE)] = [this]() { logEvent("GPS_ACTIVE_TRUE"); };
        handlers[static_cast<size_t>(EventType::GPS_FAIL)] = [this]() { logEvent("GPS_FAIL"); };
        handlers[static_cast<size_t>(EventType::IMU_ACTIVE_FALSE)] = [this]() { logEvent("IMU_ACTIVE_FALSE"); };
        handlers[static_cast<size_t>(EventType::IMU_ACTIVE_TRUE)] = [this]() { logEvent("IMU_ACTIVE_TRUE"); };
        handlers[static_cast<size_t>(EventType::IMU_FAIL)] = [this]() { logEvent("IMU_FAIL"); };
        handlers[static_cast<size_t>(EventType::FIXED_ALTITUDE_DATA_CHANGE)] = [this]() { logEvent("FIXED_ALTITUDE_DATA_CHANGE"); };
        handlers[static_cast<size_t>(EventType::FIXED_ALTITUDE_FALSE)] = [this]() { logEvent("FIXED_ALTITUDE_FALSE"); };
        handlers[static_cast<size_t>(EventType::FIXED_ALTITUDE_TRUE)] = [this]() { logEvent("FIXED_ALTITUDE_TRUE"); };
        handlers[static_cast<size_t>(EventType::FIXED_HEADING_DATA_CHANGE)] = [this]() { logEvent("FIXED_HEADING_DATA_CHANGE"); };
        handlers[static_cast<size_t>(EventType::FIXED_HEADING_FALSE)] = [this]() { logEvent("FIXED_HEADING_FALSE"); };
        handlers[static_cast<size_t>(EventType::FIXED_HEADING_TRUE)] = [this]() { logEvent("FIXED_HEADING_TRUE"); };
        handlers[static_cast<size_t>(EventType::FIXED_SPEED_DATA_CHANGE)] = [this]() { logEvent("FIXED_SPEED_DATA_CHANGE"); };
        handlers[static_cast<size_t>(EventType::FIXED_SPEED_FALSE)] = [this]() { logEvent("FIXED_SPEED_FALSE"); };
        handlers[static_cast<size_t>(EventType::FIXED_SPEED_TRUE)] = [this]() { logEvent("FIXED_SPEED_TRUE"); };

        // Airplane Events
        handlers[static_cast<size_t>(EventType::ENGINE_ON_TRUE)] = [this]() { logEvent("ENGINE_ON_TRUE"); };
        handlers[static_cast<size_t>(EventType::ENGINE_ON_FALSE)] = [this]() { logEvent("ENGINE_ON_FALSE"); };

        // Flight Events
        handlers[static_cast<size_t>(EventType::ALTITUDE_OK)] = [this]() { logEvent("ALTITUDE_OK"); };
        handlers[static_cast<size_t>(EventType::ALTITUDE_WARNING)] = [this]() { logEvent("ALTITUDE_WARNING"); };
        handlers[static_cast<size_t>(EventType::ALTITUDE_LOW)] = [this]() { logEvent("ALTITUDE_LOW"); };
        handlers[static_cast<size_t>(EventType::ALTITUDE_HIGH)] = [this]() { logEvent("ALTITUDE_HIGH"); };
        handlers[static_cast<size_t>(EventType::PITCH_OK)] = [this]() { logEvent("PITCH_OK"); };
        handlers[static_cast<size_t>(EventType::PITCH_WARNING)] = [this]() { logEvent("PITCH_WARNING"); };
        handlers[static_cast<size_t>(EventType::PITCH_LOW)] = [this]() { logEvent("PITCH_LOW"); };
        handlers[static_cast<size_t>(EventType::PITCH_HIGH)] = [this]() { logEvent("PITCH_HIGH"); };
        handlers[static_cast<size_t>(EventType::ROLL_OK)] = [this]() { logEvent("ROLL_OK"); };
        handlers[static_cast<size_t>(EventType::ROLL_LEFT_LOW)] = [this]() { logEvent("ROLL_LEFT_LOW"); };
        handlers[static_cast<size_t>(EventType::ROLL_LEFT_MID)] = [this]() { logEvent("ROLL_LEFT_MID"); };
        handlers[static_cast<size_t>(EventType::ROLL_LEFT_HIGH)] = [this]() { logEvent("ROLL_LEFT_HIGH"); };
        handlers[static_cast<size_t>(EventType::ROLL_LEFT_WARNING)] = [this]() { logEvent("ROLL_LEFT_WARNING"); };
        handlers[static_cast<size_t>(EventType::ROLL_LEFT_DANGER)] = [this]() { logEvent("ROLL_LEFT_DANGER"); };
        handlers[static_cast<size_t>(EventType::ROLL_RIGHT_LOW)] = [this]() { logEvent("ROLL_RIGHT_LOW"); };
        handlers[static_cast<size_t>(EventType::ROLL_RIGHT_MID)] = [this]() { logEvent("ROLL_RIGHT_MID"); };
        handlers[static_cast<size_t>(EventType::ROLL_RIGHT_HIGH)] = [this]() { logEvent("ROLL_RIGHT_HIGH"); };
        handlers[static_cast<size_t>(EventType::ROLL_RIGHT_WARNING)] = [this]() { logEvent("ROLL_RIGHT_WARNING"); };
        handlers[static_cast<size_t>(EventType::ROLL_RIGHT_DANGER)] = [this]() { logEvent("ROLL_RIGHT_DANGER"); };
        handlers[static_cast<size_t>(EventType::SPEED_OK)] = [this]() { logEvent("SPEED_OK"); };
        handlers[static_cast<size_t>(EventType::SPEED_LOW)] = [this]() { logEvent("SPEED_LOW"); };
        handlers[static_cast<size_t>(EventType::SPEED_HIGH)] = [this]() { logEvent("SPEED_HIGH"); };
        handlers[static_cast<size_t>(EventType::ENGINE_STALL_FALSE)] = [this]() { logEvent("ENGINE_STALL_FALSE"); };
        handlers[static_cast<size_t>(EventType::ENGINE_STALL_TRUE)] = [this]() { logEvent("ENGINE_STALL_TRUE"); };
        handlers[static_cast<size_t>(EventType::MOTOR_SPINNING_TRUE)] = [this]() { logEvent("MOTOR_SPINNING_TRUE"); };
        handlers[static_cast<size_t>(EventType::MOTOR_SPINNING_FALSE)] = [this]() { logEvent("MOTOR_SPINNING_FALSE"); };

        // Flight Plan Events
        handlers[static_cast<size_t>(EventType::WAYPOINT_SET_FALSE)] = [this]() { logEvent("WAYPOINT_SET_FALSE"); };
        handlers[static_cast<size_t>(EventType::WAYPOINT_SET_TRUE)] = [this]() { logEvent("WAYPOINT_SET_TRUE"); };
        handlers[static_cast<size_t>(EventType::WAYPOINT_DATA_UPDATE)] = [this]() { logEvent("WAYPOINT_DATA_UPDATE"); };

        // Flight Phase Events
        handlers[static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_NONE)] = [this]() { logEvent("FLIGHT_PHASE_CHANGE_NONE"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_INIT)] = [this]() { logEvent("FLIGHT_PHASE_CHANGE_INIT"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_TAXI_TO_TAKEOFF)] = [this]() { logEvent("FLIGHT_PHASE_CHANGE_TAXI_TO_TAKEOFF"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_PREP)] = [this]() { logEvent("FLIGHT_PHASE_CHANGE_TAKEOFF_PREP"); };
        handlers[static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_TAKEOFF_ROLL)] = [this]() { logEvent("FLIGHT_PHASE_CHANGE
