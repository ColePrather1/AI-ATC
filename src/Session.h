#ifndef SESSION_H
#define SESSION_H

#pragma once
#include "Common.h"
#include <atomic>

#include <array>
#include <mutex>

#include "ThreadSafeQueue.h"
#include "QuickThread.h"
#include "include/packets/packets.h"
#include "LogData.h"
#include "ControllerData.h"
#include <cstdint>

#include "GPS_Coordinate.h"

//#include "FlightSession.h"
//#include "SQL.h"

#include "Bitmask.h"


/*
    Variables belong here when at least 2 files use them
        & not header specific (e.g. current flight parameters)
*/


/*
extern namespace Session {

    // General Parameters
    extern bool quit_flag = false;

    // Controller Parameters
    extern int16_t right_x, right_y, left_x, left_y;

    // Plane Parameters
    extern uint8_t rudder_val, aileron_left_val, aileron_right_val, elevator_val, throttle_val;
    extern int p_rdr_val = -PRE_RX_THRESHOLD, p_alrn_l_val = -PRE_RX_THRESHOLD, p_alrn_r_val = -PRE_RX_THRESHOLD, p_elvr_val = -PRE_RX_THRESHOLD, p_thrt_val = -PRE_RX_THRESHOLD;
    extern uint8_t servo_defaults = {0, 90, 90, 90, 90};
    extern uint8_t feat_vals[NUM_FEATS] = {&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val};

    // Flight Parameters
    extern bool within_range = false;

    // User HUD Parameters
    extern ControlMode control_mode = ControlMode::ASSIST; 
    extern bool throttle_lock = false;
    extern bool holding_pattern = false;
    extern bool gps_active = false;
    extern bool paired = false;
    extern bool taxi_only = true;

    // Radio Parameters
    extern int rf_tx_active_pipe = 0;
    extern rf_rx_active = false;
    extern rf_tx_active = false;

}
*/


/*
class LogData {
public:
    LogData(const char* table, const char* field, std::string value) : table(table), field(field), value(value) {}
    const char* table;
    const char* field;
    //int value;
    time_t timestamp;
    std::string value;
};
class ControllerData {
public:
    ControllerData(const char* table, const char* field, std::string value) : table(table), field(field), value(value) {}
    const char* table;
    const char* field;
    //int value;
    time_t timestamp;
    std::string value;
};
*/


namespace Session {

    //ThreadSafeQueue<Packet>& m_tx_queue;


// General Parameters
    std::atomic<bool> quit_flag;

// Queues
    ThreadSafeQueue<Packet*> rx_processing_queue;
    ThreadSafeQueue<Packet> rx_queue;
    ThreadSafeQueue<Packet> tx_queue;
    //ThreadSafeQueue<LogData> log_queue;
    //ThreadSafeQueue<ControllerData> controller_queue;


// Threads
    //QuickThread rx_thread(test_setup, test_loop);

// Controller Parameters
    std::atomic<int16_t> right_x, right_y, left_x, left_y;

// Locations
    GPS_Coordinate atc_gps, plane_gps;
    
    // For safety, use atomic variables for GPS data
    std::atomic<uint16_t> plane_gps_alt;
    std::atomic<uint32_t> plane_gps_lat, plane_gps_lon;

    //uint32_t atc_latitude, atc_longitude;
    //uint16_t atc_altitude;

    //std::atomic<uint32_t> plane_gps_lat, plane_gps_lon,t;
    //std::atomic<float> plane_gps_lat, plane_gps_lon;
    //std::atomic<uint16_t> plane_gps_alt;

// Plane Parameters
    std::atomic<uint8_t> rudder_val, aileron_left_val, aileron_right_val, elevator_val, throttle_val;
    //extern std::atomic<int> p_rdr_val, p_alrn_l_val, p_alrn_r_val, p_elvr_val, p_thrt_val;
    std::array<uint8_t, NUM_FEATS> servo_defaults;
    std::array<std::atomic<uint8_t>*, NUM_FEATS> feat_vals;

// Flight Parameters  (ATC <-> Plane)
    std::atomic<ControlMode> control_mode;
    std::atomic<bool> throttle_lock, within_range, returning_home, fixed_altitude, fixed_heading;

    std::atomic<uint16_t> airplane_current_gps_heading, airplane_current_gps_speed;

    std::atomic<uint16_t> atc_pilot_distance_meters;
    std::atomic<uint32_t> atc_pilot_distance_meters_squared;
    //std::atomic<uint32_t> atc_latitude, atc_longitude
    //std::atomic<float> atc_latitude, atc_longitude;
    //std::atomic<uint16_t> atc_altitude;


// uint16_t Bitmasks
    Bitmask ATC;
    Bitmask Airplane;


void fill_atc_bm(){
    ATC[0] = throttle_lock;
    ATC[1] = within_range;
    ATC[2] = returning_home;
    ATC[3] = paired;
    ATC[4] = gps_active;
    ATC[5] = flying;
    ATC[6] = fixed_altitude;
    ATC[7] = fixed_heading;
}
    
// User HUD Parameters
    std::atomic<bool>  gps_active, paired, ctlr_paired, ctlr_active, flying;
    std::atomic<uint8_t> atc_pilot_distance_meters;

// Radio Parameters
    std::atomic<int> rf_tx_active_pipe;
    std::atomic<bool> rf_rx_active, rf_tx_active;

    // Mutex for protecting access to complex data structures
    std::mutex session_mutex;

// Functions
    // Initialize function declaration
    void initialize();
    void complex_operation();

    //void write_to_mutex();
    //void read_from_mutex();
}



//uint8_t current_rudder = Session::rudder_val.load(std::memory_order_acquire);

#endif // SESSION_H