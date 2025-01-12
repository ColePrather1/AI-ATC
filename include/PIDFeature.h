#ifndef PID_FEATURE_H
#define PID_FEATURE_H
#pragma once

#include <cstdint>

constexpr int NumPIDFeatures = 9;
enum class PIDFeature : uint8_t {
    PITCH = 0,                  // Elevator 
    ROLL = 1,                   // Aileron(s)
    YAW = 2,                    // Rudder
    HEADING = 3,                // Rudder
    ALTITUDE = 4,               // Throttle + Elevator + Flaps
    AIR_SPEED = 5,              // Elevator
    GROUND_SPEED = 6,            // Throttle
    VERTICAL_SPEED = 7,         // Elevator ( + Flaps )
    DISTANCE = 8,              // Rudder
};

#endif // PID_FEATURE_H