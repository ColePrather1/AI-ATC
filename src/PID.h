#ifndef PID_H
#define PID_H
#pragma once

#include <cstdint>

constexpr int NumPIDFeatures = 9;
enum class PIDFeatures : uint8_t {
    PITCH,                  // Elevator 
    ROLL,                   // Aileron(s)
    YAW,                    // Rudder
    HEADING,                // Rudder
    ALTITUDE,               // Throttle + Elevator + Flaps
    AIR_SPEED,              // Elevator
    GROUND_SPEED,            // Throttle
    VERTICAL_SPEED,         // Elevator ( + Flaps )
    DISTANCE,              // Rudder
};

#endif // PID_H