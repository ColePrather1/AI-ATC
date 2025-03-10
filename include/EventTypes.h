#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#pragma once
#include <cstdint>

enum class EventType : uint8_t {

// System Events
    SYSTEM_STARTUP = 0,
    SYSTEM_SHUTDOWN = 1,
    SYSTEM_RESTART = 2,
    KILL_PILOT = 3,
    FLIGHT_TIME_START_SET_TRUE = 4,
    FLIGHT_TIME_START_SET_FALSE = 5,
    FLIGHT_TIME_END_SET_TRUE = 6,
    FLIGHT_TIME_END_SET_FALSE = 7,
    FLIGHT_START_TRUE = 8,
    FLIGHT_START_FALSE = 9,

// Control Mode Events
    CONTROL_MODE_CHANGE_AUTO = 10,
    CONTROL_MODE_CHANGE_ASSIST = 11,
    CONTROL_MODE_CHANGE_MANUAL = 12,
    CONTROL_MODE_CHANGE_HOLDING = 13,
    CONTROL_MODE_CHANGE_TAXI = 14,
    CONTROL_MODE_CHANGE_EMERGENCY = 15,
    CONTROL_MODE_CHANGE_RECOVERY = 16,
    CONTROL_MODE_CHANGE_PAIRING = 17,
    // Control Mode Accept
    CONTROL_MODE_CHANGE_AUTO_ACCEPT = 18,
    CONTROL_MODE_CHANGE_ASSIST_ACCEPT = 19,
    CONTROL_MODE_CHANGE_MANUAL_ACCEPT = 20,
    CONTROL_MODE_CHANGE_HOLDING_ACCEPT = 21,
    CONTROL_MODE_CHANGE_TAXI_ACCEPT = 22,
    CONTROL_MODE_CHANGE_EMERGENCY_ACCEPT = 23,
    CONTROL_MODE_CHANGE_RECOVERY_ACCEPT = 24,
    CONTROL_MODE_CHANGE_PAIRING_ACCEPT = 25,

// Airplane Status Events
    AIRPLANE_CONNECTED_TRUE = 26,
    AIRPLANE_CONNECTED_FALSE = 27,
    PAIRED_FALSE = 28,
    PAIRED_TRUE = 29,
    PAIRED_FAIL = 30,
    THROTTLE_LOCK_DATA_CHANGE = 31,
    THROTTLE_LOCK_FALSE = 32,
    THROTTLE_LOCK_TRUE = 33,
    WITHIN_RANGE_FALSE = 34,
    WITHIN_RANGE_TRUE = 35,
    APPROACHING_BOUNDARY_FALSE = 36,
    APPROACHING_BOUNDARY_TRUE = 37,
    RETURNING_HOME_FALSE = 38,
    RETURNING_HOME_TRUE = 39,
    IS_FLYING_FALSE = 40,
    IS_FLYING_TRUE = 41,
    AIRPLANE_GPS_ACTIVE_FALSE = 42,
    AIRPLANE_GPS_ACTIVE_TRUE = 43,
    AIRPLANE_GPS_FAIL_FALSE = 44,
    AIRPLANE_GPS_FAIL_TRUE = 45,
    ATC_GPS_ACTIVE_FALSE = 46,
    ATC_GPS_ACTIVE_TRUE = 47,
    ATC_GPS_FAIL_FALSE = 48,
    ATC_GPS_FAIL_TRUE = 49,
    IMU_ACTIVE_FALSE = 50,
    IMU_ACTIVE_TRUE = 51,
    IMU_FAIL_FALSE = 52,
    IMU_FAIL_TRUE = 53,
    FIXED_ALTITUDE_DATA_CHANGE = 54,
    FIXED_ALTITUDE_FALSE = 55,
    FIXED_ALTITUDE_TRUE = 56,
    FIXED_HEADING_DATA_CHANGE = 57,
    FIXED_HEADING_FALSE = 58,
    FIXED_HEADING_TRUE = 59,
    FIXED_SPEED_DATA_CHANGE = 60,
    FIXED_SPEED_FALSE = 61,
    FIXED_SPEED_TRUE = 62,

// Airplane Events
    ENGINE_ON_TRUE = 63,
    ENGINE_ON_FALSE = 64,
    ENGINE_FAIL_FALSE = 65,
    ENGINE_FAIL_TRUE = 66,

// Flight Events
    ALTITUDE_GROUND = 67,
    ALTITUDE_OK = 68,
    ALTITUDE_WARNING_LOW = 69,
    ALTITUDE_LOW = 70,
    ALTITUDE_HIGH = 71,
    ALTITUDE_WARNING_HIGH = 72,
    PITCH_GROUND = 73,
    PITCH_OK = 74,
    PITCH_WARNING_LOW = 75,
    PITCH_LOW = 76,
    PITCH_HIGH = 77,
    PITCH_WARNING_HIGH = 78,
    ROLL_OK = 79,
    ROLL_LEFT_LOW = 80,
    ROLL_LEFT_MID = 81,
    ROLL_LEFT_HIGH = 82,
    ROLL_LEFT_WARNING = 83,
    ROLL_LEFT_DANGER = 84,
    ROLL_RIGHT_LOW = 85,
    ROLL_RIGHT_MID = 86,
    ROLL_RIGHT_HIGH = 87,
    ROLL_RIGHT_WARNING = 88,
    ROLL_RIGHT_DANGER = 89,
    AIR_SPEED_GROUND = 90,
    AIR_SPEED_OK = 91,
    AIR_SPEED_WARNING_LOW = 92,
    AIR_SPEED_LOW = 93,
    AIR_SPEED_HIGH = 94,
    AIR_SPEED_WARNING_HIGH = 95,
    ENGINE_STALL_FALSE = 96,
    ENGINE_STALL_TRUE = 97,
    MOTOR_SPINNING_TRUE = 98,
    MOTOR_SPINNING_FALSE = 99,

// Flight Plan Events
    WAYPOINT_SET_FALSE = 100,
    WAYPOINT_SET_TRUE = 101,
    WAYPOINT_ENROUTE_TRUE = 102,
    WAYPOINT_ENROUTE_FALSE = 103,
    WAYPOINT_CIRCLE = 104,
    WAYPOINT_DATA_UPDATE = 105,

// Flight Phase Events
    FLIGHT_PHASE_CHANGE_NONE = 106,
    FLIGHT_PHASE_CHANGE_INIT = 107,
    FLIGHT_PHASE_CHANGE_TAXI_TO_RUNWAY = 108,
    FLIGHT_PHASE_CHANGE_PREFLIGHT_CHECKS = 109,
    FLIGHT_PHASE_CHANGE_TAKEOFF_ROLL = 110,
    FLIGHT_PHASE_CHANGE_TAKEOFF_ASCEND = 111,
    FLIGHT_PHASE_CHANGE_CLIMB = 112,
    FLIGHT_PHASE_CHANGE_CRUISE = 113,
    FLIGHT_PHASE_CHANGE_DESCENT = 114,
    FLIGHT_PHASE_CHANGE_ALIGN_APPROACH = 115,
    FLIGHT_PHASE_CHANGE_FINAL_APPROACH = 116,
    FLIGHT_PHASE_CHANGE_FLARE = 117,
    FLIGHT_PHASE_CHANGE_TOUCHDOWN = 118,
    FLIGHT_PHASE_CHANGE_ROLL_OUT = 119,
    FLIGHT_PHASE_CHANGE_GO_AROUND = 120,
    FLIGHT_PHASE_CHANGE_HOLDING_PATTERN = 121,      // TODO: possibly remove
    FLIGHT_PHASE_CHANGE_EMERGENCY_LANDING = 122,
    FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT = 123,

// TESTING
    DB_STARTED = 124,
    DB_STOPPED = 125,
    DB_LOOPED = 126,
    EXTRA = 127,
    DB_CREATED = 128,
    RF_RX_LOOPED = 129,
    RF_RX_FAILED_TO_START = 130,
    RF_TX_FAILED_TO_START = 131,

// Shutdown
    RF_RX_START = 132,
    RF_RX_STOP = 133,
    RF_TX_START = 134,
    RF_TX_STOP = 135,
    ATC_START = 136,
    ATC_STOP = 137,
    LOGGER_START = 138,
    LOGGER_STOP = 139,
    PROCESS_START = 140,
    PROCESS_STOP = 141,
    DM_INSERT_ERROR = 142,

// Controller Events
    CONTROLLER_CONNECTED = 143,
    CONTROLLER_DISCONNECTED = 144,
    CONTROLLER_CLICKED = 145,

// Connection Events
    //PAIR_ATC_SYN = 146,
    //PAIR_ATC_SYN_ACK = 147,
    //PAIR_ATC_ACK = 148,
    //PAIR_ATC_SYN_OK = 149,

    PAIR_ATC_REQUEST = 150,         // To plane
    PAIR_ATC_REQUEST_ACK = 151,     // From plane
    PAIR_ATC_REQUEST_OK = 152,      // From plane

};

#endif // EVENT_TYPES_H
