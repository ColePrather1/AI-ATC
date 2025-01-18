#ifndef EMERGENCYCONTROLMODE_H
#define EMERGENCYCONTROLMODE_H
#include <cstdint>

namespace EmergencyControlMode {

    extern void emergencyMode(uint32_t mask);
    extern void emergency_send_btns(uint32_t mask);
    extern void emergency_send_features();

}

#endif // EMERGENCYCONTROLMODE_H