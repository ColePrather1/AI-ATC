#ifndef MANUALCONTROLMODE_H
#define MANUALCONTROLMODE_H
#include <cstdint>

namespace ManualControlMode {
    extern void manualMode(uint32_t mask);
    extern void manual_send_features();
    //extern void handleManualButtonCombinations();
    extern void handleManualButtonCombinations(uint32_t mask);
    //void manual_send_btns();

}

#endif // MANUALCONTROLMODE_H