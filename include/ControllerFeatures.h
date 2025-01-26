#ifndef CONTROLLER_FEATURES_H
#define CONTROLLER_FEATURES_H
#pragma once

#include <cstdint>

struct ControllerInput {
    int16_t raw_throttle;   //   0 : 32767
    int16_t raw_elevator;   //  -32768 : 32767
    int16_t raw_rudder;     //  -32768 : 32767
    int16_t raw_right_x;    //  -32768 : 32767
    int16_t raw_right_y;    //  -32768 : 32767
    
};

struct ControllerOutput {
    int16_t fixed_throttle;   //   0 : 32767
    int16_t fixed_elevator;   //  -32768 : 32767
    int16_t fixed_rudder;     //  -32768 : 32767
    int16_t fixed_left_aileron;    //  -32768 : 32767
    int16_t fixed_right_aileron;    //  -32768 : 32767
};



#endif // CONTROLLER_FEATURES_H