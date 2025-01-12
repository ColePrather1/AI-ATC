#ifndef FLIGHTSESSION_H
#define FLIGHTSESSION_H

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

//#include "FlightSession.h"
#include "SQL.h"


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

enum class SyncedObjects {
    

}

namespace FlightSession {

    //ThreadSafeQueue<Packet>& m_tx_queue;


// General Parameters
    std::atomic<bool> quit_flag;



// Plane Parameters
    std::atomic<uint8_t> rudder_val, aileron_left_val, aileron_right_val, elevator_val, throttle_val;
    //extern std::atomic<int> p_rdr_val, p_alrn_l_val, p_alrn_r_val, p_elvr_val, p_thrt_val;
    std::array<uint8_t, NUM_FEATS> servo_defaults;
    std::array<std::atomic<uint8_t>*, NUM_FEATS> feat_vals;

// Flight Parameters
    

// User HUD Parameters
    //std::atomic<ControlMode> control_mode;
    std::atomic<bool> throttle_lock, 
                    //holding_pattern, 
                    gps_active, 
                    paired, 
                    taxi_only,
                    within_range, 
                    returning_home,
                    ctlr_paired, 
                    ctlr_active, 
                    flying;

// Radio Parameters
    //std::atomic<int> rf_tx_active_pipe;
    //std::atomic<bool> rf_rx_active, rf_tx_active;


// ATC <-> Plane Parameters
    std::atomic<bool> atc_paired;
    std::atomic<ControlMode> control_mode;
    // within_range
    // returning_home
    // throttle_lock
    // 


}



//uint8_t current_rudder = Session::rudder_val.load(std::memory_order_acquire);

#endif // FLIGHTSESSION_H