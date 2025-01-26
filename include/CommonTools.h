#ifndef COMMON_TOOLS_H
#define COMMON_TOOLS_H
#pragma once
#include <stdint.h>

//uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
//    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}

//inline uint8_t common_map(int16_t x, int16_t in_min, int16_t in_max, uint8_t out_min, uint8_t out_max);
//inline long common_constrain(long val, long min, long max);

inline long common_constrain(long val, long min, long max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    } else {
        return val;
    }
}

inline uint8_t common_map(int16_t x, int16_t in_min, int16_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//inline int common_map(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
//    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
//}




#endif // COMMON_TOOLS_H