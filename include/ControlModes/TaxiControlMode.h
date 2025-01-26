#ifndef TAXICONTROLMODE_H
#define TAXICONTROLMODE_H
#pragma once
#include <cstdint>

namespace TaxiControlMode {

    extern void processFeatures();
    extern void processEvent(uint32_t mask);
}

#endif // TAXICONTROLMODE_H