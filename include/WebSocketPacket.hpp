#ifndef WEBSOCKET_PACKET_HPP
#define WEBSOCKET_PACKET_HPP
#include <cstdint>
//#include "ControlModes/ControlModes.h"
#include "Common.h"
#include "WebSocketPacket.hpp"

struct WebSocketPacket {
    uint16_t aircraft_distance;
    uint16_t aircraft_altitude_agl;         // AGL = above ground level
    uint32_t elapsed_flight_time;
    ControlMode control_mode;
    uint16_t aircraft_ground_speed;
    bool atc_pilot_connected;

};

#endif // WEBSOCKET_PACKET_HPP