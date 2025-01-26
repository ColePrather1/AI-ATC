#ifndef RECOVERYCONTROLMODE_H
#define RECOVERYCONTROLMODE_H
#pragma once

#include <cstdint>

namespace RecoveryControlMode {
    extern void processEvent(uint32_t mask);
    extern void processFeatures();
}

#endif // RECOVERYCONTROLMODE_H