#ifndef ASSISTCONTROLMODE_H
#define ASSISTCONTROLMODE_H
#pragma once
#include <cstdint>

namespace AssistControlMode {

    extern void processFeatures();
    extern void processEvent(uint32_t mask);

}

#endif // ASSISTCONTROLMODE_H