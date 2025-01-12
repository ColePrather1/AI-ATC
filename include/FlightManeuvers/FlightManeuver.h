#ifndef FLIGHT_MANEUVER_H
#define FLIGHT_MANEUVER_H
#pragma once

#include <cstdint>

enum class FlightManeuver : uint8_t {
    // Basic Maneuvers
    STRAIGHT_AND_LEVEL = 0,
    CLIMB = 1,
    DESCENT = 2,
    LEVEL_TURN_LEFT = 3,
    LEVEL_TURN_RIGHT = 4,
    
    // Turns
    SHALLOW_TURN_LEFT = 5,
    SHALLOW_TURN_RIGHT = 6,
    MEDIUM_TURN_LEFT = 7,
    MEDIUM_TURN_RIGHT = 8,
    
    // Climbs and Descents
    CLIMBING_TURN_LEFT = 9,
    CLIMBING_TURN_RIGHT = 10,
    DESCENDING_TURN_LEFT = 11,
    DESCENDING_TURN_RIGHT = 12,
    
    // Specific Maneuvers
    FIGURE_EIGHT = 13,
    S_TURNS = 14,
    RECTANGULAR_COURSE = 15,
    CIRCLE_AROUND_POINT = 16,
    
    // Slow Flight Maneuvers
    SLOW_FLIGHT = 17,
    STALL_RECOVERY = 18,
    
    // Landing Approaches
    STRAIGHT_IN_APPROACH = 19,
    CROSSWIND_APPROACH = 20,
    BASE_TO_FINAL_TURN = 21,
    GO_AROUND = 22,
    
    // Emergency Maneuvers
    ENGINE_OUT_GLIDE = 23,
    
    // Alignment Maneuvers
    ALIGN_WITH_HEADING = 24,
    ALIGN_WITH_RUNWAY = 25,
    INTERCEPT_COURSE = 26,
    
    // Specific RC Plane Maneuvers
    TOUCH_AND_GO = 27,
    LOW_PASS = 28,
    HOLDING_PATTERN = 29,
    
    // Basic Aerobatics (if capable)
    LOOP = 30,
    BARREL_ROLL = 31,
    
    // Training Maneuvers
    TRIM_FLIGHT = 32,
    ALTITUDE_HOLD = 33,
    HEADING_HOLD = 34,
    
    // Navigation
    RETURN_TO_HOME = 35,
    WAYPOINT_NAVIGATION = 36,
    
    // Miscellaneous
    TAKEOFF = 37,
    LANDING = 38
};



#endif // FLIGHT_MANEUVER_H