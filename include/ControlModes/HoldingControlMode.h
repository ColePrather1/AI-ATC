#ifndef HOLDINGCONTROLMODE_H
#define HOLDINGCONTROLMODE_H
#pragma once
#include <cstdint>

namespace HoldingControlMode {
    extern void processFeatures();
    extern void processEvent(uint32_t mask);
}


#endif // HOLDINGCONTROLMODE_H