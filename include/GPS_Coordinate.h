#ifndef GPS_COORDINATE_H
#define GPS_COORDINATE_H
#pragma once

#include <cstdint>

struct GPS_Coordinate {
    uint32_t latitude;      // 1e7
    uint32_t longitude;     // 1e7
    uint16_t altitude_feet; // 1e2      
};


#endif // GPS_COORDINATE_H