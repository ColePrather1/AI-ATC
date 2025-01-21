#ifndef SYSTEM_MODE_H
#define SYSTEM_MODE_H
#pragma once

#include "ButtonCombos.h"

class SystemMode {
public:

    // System
    static ButtonCombos buttonActions;

    virtual void init();
    virtual void loadEnvironment() = 0;
    //virtual void () = 0;







};




#endif // SYSTEM_MODE_H