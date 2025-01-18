#ifndef AUTOCONTROLMODE_H
#define AUTOCONTROLMODE_H
#include <cstdint>

namespace AutoControlMode {
    extern void autoMode(uint32_t mask);
    extern void auto_send_features();
    extern void auto_send_btns(uint32_t mask);
}

#endif // AUTOCONTROLMODE_H