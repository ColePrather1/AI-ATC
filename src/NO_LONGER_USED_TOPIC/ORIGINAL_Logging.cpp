#include "Logging.h"
#include "FlightDatabase.h"

static FlightDatabase* DB = nullptr;

bool Logging::logging_setup() {
    // Create Database & assign to pointer
    DB = new FlightDatabase(getNextUniqueFilename().c_str());
    return true;
}

void Logging::logging_loop(){
    DB->DB_loop();
}

// Success -> true    // Used to log by outsiders during operations
bool Logging::insertATCSystem(bool ctlr_paired, bool rf_rx_active, bool rf_tx_active){
    return DB->insertATCSystem(ctlr_paired, rf_rx_active, rf_tx_active);
}

bool Logging::insertSystemStatus(int control_mode, bool paired, bool throttle_lock, 
                        bool holding_pattern, bool taxi_only, bool gps_active){
    return DB->insertSystemStatus(control_mode, paired, throttle_lock, holding_pattern, taxi_only, gps_active);
}

bool Logging::insertFlightStatus(double battery_level, double signal_strength, bool flying){
    return DB->insertFlightStatus(battery_level, signal_strength, flying);
}

bool Logging::insertFlightVars(double pitch, double roll, double yaw, double distance){
    return DB->insertFlightVars(pitch, roll, yaw, distance);
}

bool Logging::insertServos(int throttle, int elevator, int rudder, int left_aileron, int right_aileron){
    return DB->insertServos(throttle, elevator, rudder, left_aileron, right_aileron);
}

bool Logging::insertGPSData(double latitude, double longitude, double altitude, double speed, int satellites, int signal_strength){
    return DB->insertGPSData(latitude, longitude, altitude, speed, satellites, signal_strength);
}

bool Logging::insertIMUData(double accel_x, double accel_y, double accel_z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z){
    return DB->insertIMUData(accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, mag_x, mag_y, mag_z);
}

bool Logging::insertBaroData(double pressure, double temperature, double calculated_altitude){
    return DB->insertBaroData(pressure, temperature, calculated_altitude);
}

bool Logging::insertPIDData(double roll_p, double roll_i, double roll_d, double yaw_p, double yaw_i, double yaw_d, double pitch_p, double pitch_i, double pitch_d){
    return DB->insertPIDData(roll_p, roll_i, roll_d, yaw_p, yaw_i, yaw_d, pitch_p, pitch_i, pitch_d);
}

