#ifndef AUTOCONTROLMODE_H
#define AUTOCONTROLMODE_H
#pragma once
#include <cstdint>

namespace AutoControlMode {
    extern void processFeatures();
    extern void processEvent(uint32_t mask);
}

#endif // AUTOCONTROLMODE_H