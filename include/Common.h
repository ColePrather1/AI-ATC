#ifndef COMMON_H
#define COMMON_H

#pragma once
#include <iostream>
#include <cstring>
//#include <chrono>

#include "FlightPhases/FlightPhases.h"

//#include "ThreadSafeQueue.h"

/*
    Constants belong here when at least 2 files use them
        & not header specific
*/


#define NUM_FEATS 5
#define PRE_RX_THRESHOLD 10
#define ATC_RADIUS_METERS_SQUARED 10000    // Squared to prevent expensive sqrt() in distance calculation when not needed
#define ATC_RADIUS_METERS 100           // 100 meters


#define PAYLOAD_SIZE 24 // 24 chars in payload array

// namespace for RF constant global external var of payload size to keep things clean
//inline namespace RF { 
//    inline constexpr int PAYLOAD_SIZE = 24; 
//}



enum class Flaps : uint8_t { DEGREES_0 = 0,
                             DEGREES_5 = 1,
                             DEGREES_10 = 2,
                             DEGREES_15 = 3,
                             DEGREES_20 = 4,
                             DEGREES_25 = 5,
                             DEGREES_30 = 6,
                             DEGREES_35 = 7,
                             DEGREES_40 = 8,
                             DEGREES_45 = 9,
                             DEGREES_50 = 10,
                             DEGREES_55 = 11,
                             DEGREES_60 = 12,
                             DEGREES_75 = 13,
                             DEGREES_90 = 14
                             };
//enum class ControlMode { AUTO, MANUAL, ASSIST, EMERGENCY, PAIRING};
enum class ControlMode : uint8_t { AUTO,
                                   MANUAL,
                                   ASSIST,
                                   EMERGENCY,
                                   PAIRING,
                                   HOLDING,
                                   TAXI,
                                   RECOVERY
                                   };


enum class TypeLevel : uint8_t {
    GROUND = 0,
    OK = 1,
    WARNING_LOW = 2,
    DANGER_LOW = 3,
    WARNING_HIGH = 4,
    DANGER_HIGH = 5
};

enum class RollLevel : uint8_t {
    OK = 0,
    LEFT_LOW = 1,
    LEFT_MID = 2,
    LEFT_HIGH = 3,
    LEFT_WARNING = 4,
    LEFT_DANGER = 5,
    RIGHT_LOW = 6,
    RIGHT_MID = 7,
    RIGHT_HIGH = 8,
    RIGHT_WARNING = 9,
    RIGHT_DANGER = 10
};

/*
enum class AltitudeLevel : uint8_t {
    GROUND = 0,
    OK = 1,
    WARNING_LOW = 2,
    LOW = 3,
    HIGH = 4,
    WARNING_HIGH = 5,
};

enum class PitchLevel : uint8_t {
    GROUND = 0,
    OK = 1,
    WARNING_LOW = 2,
    LOW = 3,
    HIGH = 4,
    WARNING_HIGH = 5,
};
*/


/*
enum class EventType {
    RX_DATA_RECEIVED,
    TX_DATA_READY,
    LOG_DATA_READY,
    CONTROLLER_DATA_READY,
    COMPUTATION_COMPLETE,
    SHUTDOWN
};
struct Event {
    EventType type;
    void* data;
};
*/




//uint8_t constrain(uint8_t val, uint8_t min, uint8_t max);

//inline uint8_t common_constrain(uint8_t val, uint8_t min, uint8_t max) {
//    if (val < min) {
//        return min;
//    } else if (val > max) {
//        return max;
//    } else {
//        return val;
//    }
//}

//inline long common_constrain(long val, long min, long max);


#endif // COMMON_H