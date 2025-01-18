#ifndef ASSISTCONTROLMODE_H
#define ASSISTCONTROLMODE_H
#pragma once
#include <cstdint>

namespace AssistControlMode {
    extern void assistMode(uint32_t mask);
    extern void assist_send_features();
    extern void assist_send_btns(uint32_t mask);

}

#endif // ASSISTCONTROLMODE_H