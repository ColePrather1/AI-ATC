#ifndef LOGGING_H
#define LOGGING_H
#pragma once

#include <cstdint>
#include "PIDFeature.h"

//#include "../src/EventTypes.h"
#include "EventTypes.h"

const uint64_t EVENT_LOG_NULL_DATA = 0;

namespace Logging
{
    // Logging Functions

    bool startLogger();
    void stopLogger();

    //bool logging_setup();
    //void logging_loop();
    //void logging_stop();



    // System Logging


    // Flight Data
    bool insertPlaneState(double pitch, double roll, double yaw);
    bool insertServoData(uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    bool insertGPSData(uint32_t latitude, uint32_t longitude, uint16_t altitude, uint16_t distance_meters);
    bool insertGPSEnvData(uint16_t heading, uint16_t speed, uint8_t satellites, int8_t signal_strength);

    //bool insertAccelData(uint32_t accel_x, uint32_t accel_y, uint32_t accel_z);
    //bool insertGyroData(uint32_t gyro_x, uint32_t gyro_y, uint32_t gyro_z);
    //bool insertMagData(uint32_t mag_x, uint32_t mag_y, uint32_t mag_z);
    //bool insertBaroData(uint32_t pressure, uint32_t temperature, uint32_t baro_altitude);

    bool insertAccelData(int16_t accel_x, int16_t accel_y, int16_t accel_z);
    bool insertGyroData(int16_t gyro_x, int16_t gyro_y, int16_t gyro_z);
    bool insertMagData(int16_t mag_x, int16_t mag_y, int16_t mag_z);
    bool insertBaroData(int16_t pressure, int16_t temperature, int16_t baro_altitude);
    bool insertPIDData(PIDFeature feature, double Kp, double Ki, double Kd);

    // Event Logging
    bool insertEventLog(EventType event_type); 
    bool insertEventLog(EventType event_type, uint8_t data);
    bool insertEventLog(EventType event_type, uint16_t data);
    bool insertEventLog(EventType event_type, uint32_t data);
    bool insertEventLog(EventType event_type, uint64_t data);
    //bool insertEventLog(EventType event_type, uint32_t timestamp); 
    bool insertEventLog(EventType event_type, uint8_t data, uint32_t timestamp);


} // namespace Logging

#endif // LOGGING_H