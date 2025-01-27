#ifndef COMMON_TOOLS_H
#define COMMON_TOOLS_H
#pragma once
#include <stdint.h>

// TODO: Handle types better
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

#endif // COMMON_TOOLS_H