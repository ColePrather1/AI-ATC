#ifndef BUTTON_COMBOS_H
#define BUTTON_COMBOS_H
#pragma once
#include <array>

#include <inttypes.h>

// PS5 Define button masks
#define BTN_CROSS    (1 << 0)
#define BTN_CIRCLE   (1 << 1)
#define BTN_SQUARE   (1 << 2)
#define BTN_TRIANGLE (1 << 3)
#define BTN_L1       (1 << 4)
#define BTN_R1       (1 << 5)
#define BTN_L2       (1 << 6)
#define BTN_R2       (1 << 7)
#define BTN_SHARE    (1 << 8)
#define BTN_OPTIONS  (1 << 9)
#define BTN_L3       (1 << 10)
#define BTN_R3       (1 << 11)
#define BTN_PS       (1 << 12)
#define BTN_TOUCHPAD (1 << 13)
#define BTN_MUTE     (1 << 14)



class ButtonCombos {
    //static std::array<std::array<uint32_t, 2>, 4> button_combos = { { { BTN_CROSS, BTN_CIRCLE }, { BTN_CROSS, BTN_SQUARE }, { BTN_CROSS, BTN_TRIANGLE }, { BTN_L1, BTN_R1 } } };

    // System
    virtual void loadEnvironment() = 0;
    //virtual void () = 0;

    // Button Combos
    virtual void cross() = 0;
    virtual void circle() = 0;
    virtual void square() = 0;
    virtual void triangle() = 0;
    virtual void l1() = 0;
    virtual void r1() = 0;
    virtual void share() = 0;
    virtual void options() = 0;
    virtual void l3() = 0;
    virtual void r3() = 0;
    virtual void ps() = 0;
    virtual void touchpad() = 0;
    virtual void mute() = 0;
    virtual void cross_circle() = 0;
    virtual void l1_r1() = 0;
    virtual void l3_r3() = 0;
}







#endif // BUTTON_COMBOS_H