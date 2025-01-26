#ifndef MANUALCONTROLMODE_H
#define MANUALCONTROLMODE_H
#pragma once
#include <cstdint>

namespace ManualControlMode {

    extern void processFeatures();
    // TODO: Rename to match rest
    extern void processEvent(uint32_t mask);

    //extern void manualMode(uint32_t mask);
    //extern void manual_send_features();
    //extern void handleManualButtonCombinations();
    //void manual_send_btns();


}

#endif // MANUALCONTROLMODE_H