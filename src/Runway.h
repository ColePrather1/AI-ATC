#ifndef RUNWAY_H
#define RUNWAY_H
#pragma once

#include "GPS_Coordinate.h"

class Line {
public:
    GPS_Coordinate start;
    GPS_Coordinate end;
    uint16_t length;
    uint16_t heading;
};


class Runway {
public:
    GPS_Coordinate start_left;
    GPS_Coordinate start_right;
    GPS_Coordinate end_left;
    GPS_Coordinate end_right;
};

#endif // RUNWAY_H