#ifndef COMMON_H
#define COMMON_H

#pragma once
#include <iostream>
#include <cstring>
#include <chrono>
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



enum class Flaps { OFF, LOW, MID, HIGH};
//enum class ControlMode { AUTO, MANUAL, ASSIST, EMERGENCY, PAIRING};
enum class ControlMode { AUTO, MANUAL, ASSIST, EMERGENCY, PAIRING, HOLDING, TAXI, RECOVERY};

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


uint8_t constrain(uint8_t val, uint8_t min, uint8_t max);
uint8_t constrain(uint8_t val, uint8_t min, uint8_t max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    } else {
        return val;
    }
}


#endif // COMMON_H