#ifndef MY_TIME_H
#define MY_TIME_H
#pragma once

#include <cstdint>

#include <chrono>
#include <ctime>


namespace myTime {
    uint32_t getTimestamp();
    std::chrono::milliseconds getFlightTime();
}


#endif // MY_TIME_H