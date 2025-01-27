#ifndef MANUALCONTROLMODE_H
#define MANUALCONTROLMODE_H
#pragma once
#include <cstdint>

namespace ManualControlMode {

    extern void processFeatures();
    // TODO: Rename to match rest
    extern void processEvent(uint32_t mask);
}

#endif // MANUALCONTROLMODE_H