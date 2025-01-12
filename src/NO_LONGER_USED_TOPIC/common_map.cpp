#include "common_map.h"

uint8_t common_map(int16_t x, int16_t in_min, int16_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
