#ifndef TAXICONTROLMODE_H
#define TAXICONTROLMODE_H
#pragma once
#include <cstdint>

namespace TaxiControlMode {
    extern void taxiMode(uint32_t mask);
    extern void send_features();
    extern void send_btns(uint32_t mask);
}

#endif // TAXICONTROLMODE_H