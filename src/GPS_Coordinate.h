#ifndef GPS_COORDINATE_H
#define GPS_COORDINATE_H
#pragma once

#include <cstdint>

struct GPS_Coordinate {

    uint32_t latitude;      // 1e7
    uint32_t longitude;     // 1e7
    uint16_t altitude_feet; // 1e2      

    //uint16_t speed;
    //uint8_t satellites;
    //uint8_t signal_strength;

    //double latitude;
    //double longitude;
    //double altitude;
    //double speed;
    //int satellites;
    //int signal_strength;
};


#endif // GPS_COORDINATE_H