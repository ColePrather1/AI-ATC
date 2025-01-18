#ifndef HOLDINGCONTROLMODE_H
#define HOLDINGCONTROLMODE_H
#pragma once
#include <cstdint>

namespace HoldingControlMode {
    extern void holdingMode(uint32_t mask);
    //extern void holding_send_features();
    extern void holding_send_btns(uint32_t mask);
}


#endif // HOLDINGCONTROLMODE_H