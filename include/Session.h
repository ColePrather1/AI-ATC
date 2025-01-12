#ifndef SESSION_H
#define SESSION_H

#pragma once
#include "Common.h"
#include <chrono>
#include <atomic>
#include <array>
#include <cstdint>
#include "GPS_Coordinate.h"

//#include <mutex>

//#include "ThreadSafeQueue.h"
//#include "QuickThread.h"

//#include "../include/packets/packets.h"
//#include "packets/packets.h"
//#include "ControllerData.h"


//#include "FlightSession.h"
//#include "SQL.h"

//#include "Bitmask.h"


/*
    Variables belong here when at least 2 files use them
        & not header specific (e.g. current flight parameters)
*/


inline namespace Session {

// General Parameters
    inline std::atomic<bool> quit_flag {false}, logger_started {false};
    inline std::atomic<bool> logger_running {false}, logger_thread_active {false};



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
    inline std::atomic<ControlMode> control_mode;      // TODO: In all files, change to active_control_mode
    inline std::atomic<bool> throttle_lock, 

                      within_range, 
                      approaching_boundary,
                      returning_home, 
                      isWaypointSet,
                      isEnrouteToWaypoint,
                      isCircleWaypoint,
                      //isWaypointActive,
                      //isWaypointUpdated,

                      fixed_altitude, 
                      fixed_heading,
                      fixed_speed,

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

    //std::atomic<double> atc_pilot_distance_meters;     // TODO: in Packets & SQL, fix Lat/Lon types from int32_t to double           // ====  std::atomic<unsigned short>
    inline std::atomic<uint16_t> atc_pilot_distance_meters;      // ====  std::atomic<unsigned short>
    inline std::atomic<uint32_t> atc_pilot_distance_meters_squared;

// uint16_t Bitmasks
    //Bitmask ATC;
    //Bitmask Airplane;


// User HUD Parameters
    inline std::atomic<bool> paired, ctlr_paired, ctlr_active;
   
// Radio Parameters
    inline std::atomic<int> rf_tx_active_pipe {5};
    inline std::atomic<bool> rf_rx_active {false}, rf_tx_active {false};



// Functions
    inline void initialize();
}



#endif // SESSION_H