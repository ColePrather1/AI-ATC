#ifndef PAIRINGCONTROLMODE_H
#define PAIRINGCONTROLMODE_H
#pragma once
#include <cstdint>

namespace PairingControlMode {
    extern void processFeatures();
    extern void processEvent(uint32_t mask);
}

#endif // PAIRINGCONTROLMODE_H