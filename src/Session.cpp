#include "Session.h"


//extern int p_rdr_val = -PRE_RX_THRESHOLD, p_alrn_l_val = -PRE_RX_THRESHOLD, p_alrn_r_val = -PRE_RX_THRESHOLD, p_elvr_val = -PRE_RX_THRESHOLD, p_thrt_val = -PRE_RX_THRESHOLD;
//extern uint8_t servo_defaults[NUM_FEATS] = {0, 90, 90, 90, 90};

//extern uint8_t* feat_vals[NUM_FEATS] = {&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val};
//extern uint8_t* feat_vals[NUM_FEATS] = {&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val};

//std::array<std::atomic<uint8_t>*, NUM_FEATS> feat_vals ;

//std::atomic<uint8_t>* 




// Mutex for protecting access to complex data structures
//extern std::mutex session_mutex;

//Session::rudder_val.store(68, std::memory_order_release);

/*
    TODO: Initialize SQL db events_log with base statuses for each type of event/status
*/

void Session::initialize(){

    // Controller Parameters
    //extern std::atomic<int16_t> right_x, right_y, left_x, left_y;

    // Plane Parameters
    rudder_val = 0;
    throttle_val = 0;
    elevator_val = 0;
    Session::aileron_left_val = 0;
    Session::aileron_right_val = 0;
    //rudder_val.store(68, std::memory_order_release);


    //Session::servo_defaults = {0, 90, 90, 90, 90};

    Session::feat_vals = {&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val};
    //Session::feat_vals.store({&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val}, std::memory_order_release);
    //Session::feat_vals


    // Flight Parameters
    //Session::within_range = false;
    Session::within_range.store(false, std::memory_order_release);
 
    // User HUD Parameters
    //Session::quit_flag = false;
    //Session::control_mode = ControlMode::ASSIST;
    //Session::throttle_lock = false; 
    //Session::holding_pattern = false;
    //Session::gps_active = false;
    //Session::paired = false;
    //Session::taxi_only = true;
    //Session::ctlr_mode = false;

    Session::quit_flag.store(false, std::memory_order_release);
    Session::control_mode.store(ControlMode::ASSIST, std::memory_order_release);
    Session::throttle_lock.store(false, std::memory_order_release);
    Session::holding_pattern.store(false, std::memory_order_release);
    Session::gps_active.store(false, std::memory_order_release);
    Session::paired.store(false, std::memory_order_release);
    Session::taxi_only.store(true, std::memory_order_release);
    Session::ctlr_paired.store(false, std::memory_order_release);
    Session::flying.store(false, std::memory_order_release);



    // Radio Parameters
    //Session::rf_tx_active_pipe = 0;
    //Session::rf_rx_active = false;
    //Session::rf_tx_active = false;

    Session::rf_tx_active_pipe.store(0, std::memory_order_release);
    Session::rf_rx_active.store(false, std::memory_order_release);
    Session::rf_tx_active.store(false, std::memory_order_release);

}


void Session::complex_operation()
{
    std::lock_guard<std::mutex> lock(Session::session_mutex);
    //std::lock_guard<std::mutex> lock(session_mutex);
    // Perform complex operations here
}


void write_to_mutex() {
    //std::lock_guard<std::mutex> lock(Session::session_mutex);
    Session::rudder_val.store(68, std::memory_order_release);
    // Perform operations that require the mutex here
}

void read_from_mutex() {
    std::lock_guard<std::mutex> lock(Session::session_mutex);
    // Perform operations that require the mutex here
}

