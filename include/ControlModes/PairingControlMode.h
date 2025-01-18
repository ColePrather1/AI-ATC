#ifndef PAIRINGCONTROLMODE_H
#define PAIRINGCONTROLMODE_H
#pragma once
#include <cstdint>

namespace PairingControlMode {
    extern void pairingMode(uint32_t mask);
    extern void send_features();
    extern void send_btns(uint32_t mask);
}

#endif // PAIRINGCONTROLMODE_H