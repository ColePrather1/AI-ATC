#ifndef EMERGENCYCONTROLMODE_H
#define EMERGENCYCONTROLMODE_H
#pragma once
#include <cstdint>

namespace EmergencyControlMode {

    extern void processEvent(uint32_t mask);
    extern void processFeatures();

}

#endif // EMERGENCYCONTROLMODE_H