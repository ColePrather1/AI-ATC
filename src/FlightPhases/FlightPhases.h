#ifndef FLIGHT_PHASES_H
#define FLIGHT_PHASES_H
#pragma once

#include <cstdint>

enum class FlightPhase : uint8_t {
    // Define your flight phases here
    INIT,
    TAXI_TO_TAKEOFF,
    TAKEOFF_PREP,
    TAKEOFF_ROLL,
    TAKEOFF,
    CLIMB,
    CRUISE,
    DESCENT,
    ALIGN_APPROACH,
    FINAL_APPROACH,        // Descending to 0.5m
    FLARE,                // LiDAR reads ground (less than 0.5m)
    TOUCHDOWN,            // LiDAR reads ground (less than 0.1m)
    ROLL_OUT,            // Slowdown and stop
    //LANDING_DESCENT,
    //LANDING,
    //LANDING_FINAL,
    GO_AROUND,
    HOLDING_PATTERN,
    EMERGENCY_LANDING,
    COMPLETE_FLIGHT
};


#endif // FLIGHT_PHASES_H