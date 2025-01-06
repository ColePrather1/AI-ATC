#ifndef LOGGING_H
#define LOGGING_H
#pragma once

#include <cstdint>
#include "PID.h"

namespace Logging
{
    // Logging Functions
    bool logging_setup();
    void logging_loop();

    // System Logging
    bool insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active);
    bool insertSystemStatus(int control_mode, bool paired, bool throttle_lock, bool holding_pattern, bool taxi_only, bool gps_active);
    bool insertSystemStatus(int control_mode, uint32_t Status);
    bool insertFlightStatus(double battery_level, double signal_strength, bool flying);

    // Flight Data
    bool insertFlightVars(double pitch, double roll, double yaw);
    bool insertServos(uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron);
    //bool insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength);
    
    // TODO: Implement
    bool insertGPSData(uint32_t latitude, uint32_t longitude, uint16_t altitude, uint16_t distance_meters);
    bool insertGPSEnvData(uint16_t heading, uint16_t speed, uint8_t satellites, int8_t signal_strength);


    //bool insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z);
    // Vector3 + Header
    // IMU Data (Vector3)
    bool insertAccelData(double accel_x, double accel_y, double accel_z);
    bool insertGyroData(double gyro_x, double gyro_y, double gyro_z);
    bool insertMagData(double mag_x, double mag_y, double mag_z);
    bool insertBaroData(double pressure, double temperature, double calculated_altitude);

    bool insertPIDData(PIDFeatures feature, double p, double i, double d);

    bool insertEventLog(EventType event_type, uint8_t metadata);

    // TODO: Implement in other files for SQL
    //bool insertStatusOnChange(EventType event_type, std::string event_message, uint32_t timestamp);

    //bool insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d);
} // namespace Logging

#endif // LOGGING_H