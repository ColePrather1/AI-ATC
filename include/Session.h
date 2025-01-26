#ifndef SESSION_H
#define SESSION_H

#pragma once
#include "Common.h"
#include <chrono>
#include <atomic>
#include <array>
#include <cstdint>
#include "GPS_Coordinate.h"

//#include "FlightSession.h"
//#include "Bitmask.h"


/*
    Variables belong here when at least 2 files use them
        & not header specific (e.g. current flight parameters)
*/


inline namespace Session {

// DB Tools
    inline std::atomic<bool> sql_finalized {false}, sql_closed {false};

// General Parameters
    inline std::atomic<bool> program_finished {false};
    inline std::atomic<bool> quit_flag {false};
    inline std::atomic<bool> logger_started {false}; // TODO: Transition to ServiceStates within respective files
    //  logger_running {false}, logger_thread_active {false},   // TODO: Stop using all these
// Service Active
    inline std::atomic<bool> atc_active {false};
    inline std::atomic<bool> ctlr_active {false};
    inline std::atomic<bool> logger_active {false};
    inline std::atomic<bool> rf_rx_active {false};
    inline std::atomic<bool> rf_tx_active {false};
    inline std::atomic<bool> process_active {false};

// Thread Loop Active
    //inline std::atomic<bool> atc_loop_active {false};
    inline std::atomic<bool> ctlr_loop_active {false};
    inline std::atomic<bool> logger_loop_active {false};
    inline std::atomic<bool> rf_rx_loop_active {false};
    inline std::atomic<bool> rf_tx_loop_active {false};
    inline std::atomic<bool> process_loop_active {false};

// Thread Shutdown In-Progress
    inline std::atomic<bool> atc_shtdwn {false};    // True when at least one of the below is true
    inline std::atomic<bool> ctlr_shtdwn {false};
    inline std::atomic<bool> logger_shtdwn {false};
    inline std::atomic<bool> rf_rx_shtdwn {false};
    inline std::atomic<bool> rf_tx_shtdwn {false};
    inline std::atomic<bool> process_shtdwn {false};

// Thread Finished Flag
    inline std::atomic<bool> atc_finished {false};
    inline std::atomic<bool> ctlr_finished {false};
    inline std::atomic<bool> logger_finished {false};
    inline std::atomic<bool> rf_rx_finished {false};
    inline std::atomic<bool> rf_tx_finished {false};
    inline std::atomic<bool> process_finished {false};


// Controller Parameters
    //std::atomic<int16_t> right_x, right_y, left_x, left_y;

// Locations
    inline GPS_Coordinate atc_gps, plane_gps;

    inline std::atomic<uint16_t> atc_gps_alt;
    inline std::atomic<double> atc_gps_lat, atc_gps_lon;   // TODO: in Packets & SQL, fix Lat/Lon types from int32_t to double
    inline double calc_atc_gps_lat, calc_atc_gps_lon;
    inline std::atomic<uint16_t> plane_gps_alt;
    inline std::atomic<double> plane_gps_lat, plane_gps_lon;    // TODO: in Packets & SQL, fix Lat/Lon types from int32_t to double

// Plane Parameters
    inline std::atomic<uint8_t> rudder_val, aileron_left_val, aileron_right_val, elevator_val, throttle_val, throttle_lock_val;
    inline std::array<uint8_t, NUM_FEATS> servo_defaults;
    inline std::array<std::atomic<uint8_t>*, NUM_FEATS> feat_vals;


// Airplane Status  (ATC <-> Plane)
    inline std::atomic<TypeLevel> plane_altitude_level, plane_pitch_level, plane_air_speed_level;
    inline std::atomic<RollLevel> plane_roll_level;
    inline std::atomic<FlightPhase> airplane_active_flight_phase; 
    inline std::atomic<ControlMode> control_mode{ControlMode::PAIRING};      // TODO: In all files, change to active_control_mode
    inline std::atomic<bool> throttle_lock{false}, 

                      within_range, 
                      approaching_boundary,
                      returning_home, 
                      isWaypointSet,
                      isEnrouteToWaypoint,
                      isCircleWaypoint,
                      //isWaypointUpdated,

                      imu_active,
                      imu_fail,
                      isFlying,
                      airplane_gps_active,
                      airplane_gps_fail,
                      atc_gps_active,
                      atc_gps_fail,
                      engine_active,
                      engine_fail,
                      engine_stall,
                      isMotorSpinning
                      ;

    inline std::atomic<uint16_t> airplane_current_gps_heading, 
                          airplane_current_gps_speed;

// Flight Parameters  (ATC <-> Plane)
    inline std::atomic<std::chrono::steady_clock::time_point> flightStartTime;
    inline std::atomic<uint32_t> flight_time_start, flight_time_end;
    inline std::atomic<uint16_t> fixed_plane_heading, fixed_plane_speed, fixed_plane_altitude;
    inline std::atomic<uint32_t> waypoint_lat, waypoint_lon, waypoint_alt;

    //std::atomic<double> atc_pilot_distance_meters;     // TODO: in Packets & SQL, fix Lat/Lon types from int32_t to double
    inline std::atomic<uint16_t> atc_pilot_distance_meters;
    inline std::atomic<uint32_t> atc_pilot_distance_meters_squared;

// uint16_t Bitmasks
    //Bitmask ATC;
    //Bitmask Airplane;


// User HUD Parameters
    inline std::atomic<bool> paired{false}, ctlr_paired{false}, plane_connected{false};
   
// Radio Parameters
    inline std::atomic<int> rf_tx_active_pipe {5};


// Functions
    inline void initialize();
}



#endif // SESSION_H