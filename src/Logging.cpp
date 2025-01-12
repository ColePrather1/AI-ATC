
#include "Logging.h"
#include "Session.h"
//#include "include/Logging.h"
//#include "../include/Logging.h"


#include "FlightDatabase.h"

#include "myTime.h"

static FlightDatabase* DB = nullptr;

//std::thread dbThread(&FlightDatabase::DB_loop, DB);


bool Logging::startLogger(){
    // Create Database & assign to pointer
    //DB = new FlightDatabase(getNextUniqueFilename().c_str());
    DB = new FlightDatabase(getNextUniqueFilename());
    while (!Session::logger_thread_active.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    DB->startDBLoop();
    return true;    
}

void Logging::stopLogger(){
    DB->stopDBLoop();
    delete DB;
    return;
}

/*
bool Logging::logging_setup() {
    // Create Database & assign to pointer
    DB = new FlightDatabase(getNextUniqueFilename().c_str());
    return true;
}

void Logging::logging_loop(){
    DB->DB_loop();
}


void Logging::logging_finalize(){
    DB->disableDBLoop();
    DB->finalizeStatements();
    delete DB;
}

*/


// Success -> true    // Used to log by outsiders during operations

bool Logging::insertPlaneState(double pitch, double roll, double yaw){
    return DB->insertPlaneState(pitch, roll, yaw);
}

bool Logging::insertServoData(uint8_t throttle, uint8_t elevator, uint8_t rudder, uint8_t left_aileron, uint8_t right_aileron){
    return DB->insertServoData(throttle, elevator, rudder, left_aileron, right_aileron);
}

bool Logging::insertGPSData(uint32_t latitude, uint32_t longitude, uint16_t altitude, uint16_t distance_meters){
// TODO: Implement decimal precision, need to check GPS data first
    return DB->insertGPSData(static_cast<double>(latitude*1e-7), 
                            static_cast<double>(longitude*1e-7),
                            static_cast<double>(altitude*1e-1),
                            static_cast<double>(distance_meters*1e-1)
                            );
}

bool Logging::insertGPSEnvData(uint16_t heading, uint16_t speed, uint8_t satellites, int8_t signal_strength){
// TODO: Implement decimal precision, need to check GPS data first
    //return DB->insertGPSEnvData(heading, speed, satellites, signal_strength);
    return DB->insertGPSEnvData(static_cast<double>(heading*1e-2), 
                            static_cast<double>(speed*1e-1),
                            static_cast<int>(satellites),
                            static_cast<int>(signal_strength)
                            );
}

bool Logging::insertAccelData(int16_t accel_x, int16_t accel_y, int16_t accel_z){
    return DB->insertAccelData(accel_x*0.01f, accel_y*0.01f, accel_z*0.01f);
}
bool Logging::insertGyroData(int16_t gyro_x, int16_t gyro_y, int16_t gyro_z){
    return DB->insertGyroData(gyro_x*0.01f, gyro_y*0.01f, gyro_z*0.01f);
}
bool Logging::insertMagData(int16_t mag_x, int16_t mag_y, int16_t mag_z){
    return DB->insertMagData(mag_x*0.01f, mag_y*0.01f, mag_z*0.01f);
}
bool Logging::insertBaroData(int16_t pressure, int16_t temperature, int16_t baro_altitude){
    return DB->insertBaroData(pressure*0.01f, temperature*0.01f, baro_altitude*0.01f);
}
bool Logging::insertPIDData(PIDFeature feature, double Kp, double Ki, double Kd){
    return DB->insertPIDData(feature, Kp, Ki, Kd);
}

bool Logging::insertEventLog(EventType event_type){
    return DB->insertEventLog(event_type, myTime::getTimestamp(), EVENT_LOG_NULL_DATA);
}
bool Logging::insertEventLog(EventType event_type, uint8_t data){
    return DB->insertEventLog(event_type, myTime::getTimestamp(), data);
}
bool Logging::insertEventLog(EventType event_type, uint16_t data){
    return DB->insertEventLog(event_type, myTime::getTimestamp(), data);
}
bool Logging::insertEventLog(EventType event_type, uint32_t data){
    return DB->insertEventLog(event_type, myTime::getTimestamp(), data);
}
bool Logging::insertEventLog(EventType event_type, uint64_t data){
    return DB->insertEventLog(event_type, myTime::getTimestamp(), data);
}
bool Logging::insertEventLog(EventType event_type, uint8_t data, uint32_t timestamp){
    return DB->insertEventLog(event_type, timestamp, data);
}

/*
bool Logging::insertEventLog(EventType event_type, uint32_t timestamp){
    return DB->insertEventLog(event_type, timestamp, EVENT_LOG_NULL_DATA);
}
*/


/*
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
*/


