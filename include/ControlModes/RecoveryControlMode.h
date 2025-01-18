#ifndef RECOVERYCONTROLMODE_H
#define RECOVERYCONTROLMODE_H
#pragma once

#include <cstdint>

namespace RecoveryControlMode {
    extern void recoveryMode(uint32_t mask);
    extern void recovery_send_btns(uint32_t mask);
}

#endif // RECOVERYCONTROLMODE_H