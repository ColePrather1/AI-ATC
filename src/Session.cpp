
#include "Session.h"

//#include "../include/Session.h"

/*
namespace Session {
// Initialize atomic variables
std::atomic<bool> quit_flag(false);
std::atomic<bool> logger_running(false);
std::atomic<bool> logger_thread_active(false);
//std::atomic<int16_t> right_x(0), right_y(0), left_x(0), left_y(0);
std::atomic<uint16_t> atc_gps_alt(0);
std::atomic<double> atc_gps_lat(0.0), atc_gps_lon(0.0);
std::atomic<uint16_t> plane_gps_alt(0);
std::atomic<double> plane_gps_lat(0.0), plane_gps_lon(0.0);

std::atomic<uint8_t> rudder_val(0), aileron_left_val(0), aileron_right_val(0), elevator_val(0), throttle_val(0), throttle_lock_val(0);
std::array<uint8_t, NUM_FEATS> servo_defaults = {0, 90, 90, 90, 90};
std::array<std::atomic<uint8_t>*, NUM_FEATS> feat_vals = {&throttle_val, &elevator_val, &rudder_val, &aileron_left_val, &aileron_right_val};

std::atomic<ControlMode> control_mode(ControlMode::PAIRING);
std::atomic<bool> throttle_lock(false), within_range(false), approaching_boundary(false), returning_home(false),
                  isWaypointSet(false), isEnrouteToWaypoint(false), isCircleWaypoint(false),
                  fixed_altitude(false), fixed_heading(false), fixed_speed(false),
                  imu_active(false), imu_fail(false), isFlying(false), airplane_gps_active(false),
                  airplane_gps_fail(false), atc_gps_active(false), atc_gps_fail(false),
                  engine_active(false), engine_fail(false), engine_stall(false), isMotorSpinning(false);

std::atomic<FlightPhase> airplane_active_flight_phase(FlightPhase::GROUNDED);

std::atomic<uint16_t> airplane_current_gps_heading(0), airplane_current_gps_speed(0);
std::atomic<std::chrono::steady_clock::time_point> flightStartTime;
std::atomic<uint16_t> fixed_plane_heading(0), fixed_plane_speed(0), fixed_plane_altitude(0);
std::atomic<uint32_t> waypoint_lat(0), waypoint_lon(0), waypoint_alt(0);
std::atomic<uint16_t> atc_pilot_distance_meters(0);
std::atomic<uint32_t> atc_pilot_distance_meters_squared(0);

std::atomic<TypeLevel> plane_altitude_level(TypeLevel::NORMAL), plane_pitch_level(TypeLevel::NORMAL), plane_air_speed_level(TypeLevel::NORMAL);
std::atomic<RollLevel> plane_roll_level(RollLevel::LEVEL);

std::atomic<bool> paired(false), ctlr_paired(false), ctlr_active(false);
std::atomic<int> rf_tx_active_pipe(0);
std::atomic<bool> rf_rx_active(false), rf_tx_active(false);

} // namespace Session
*/

/*
    TODO: Initialize SQL db events_log with base statuses for each type of event/status
*/

/*
void Session::initialize(){
    quit_flag = false;
    logger_running = false;
    logger_thread_active = false;
}
*/
