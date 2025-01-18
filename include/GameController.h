#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
//#include "atc.h"
//#include "atc_rf.h"
//#include <atomic>



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

namespace GameController {

    inline SDL_GameController* controller;
    inline uint32_t buttonMask;
    //uint8_t controller_defaults;
    //std::atomic<uint32_t> buttonMask;
    
    //extern uint8_t controller_defaults = {0, 90, 90, 90, 90};
    //uble plane_default_cruise = {0,0,0,0,0,0};

    //void calibrate_controller() {
    //    controller_defaults[0] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    //    controller_defaults[1] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    //    controller_defaults[2] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
    //    controller_defaults[3] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    //}


    //uint32_t getButtonCombinationMask(SDL_GameController* controller);
    //uint32_t getButtonCombinationMask();
    extern void getButtonCombinationMask();
    //void handleButtonCombinations();
    //void handleButtonCombinations(uint32_t& mask);
    extern bool controller_setup();

    extern bool tryConnect();
    extern bool waitForConnection();

    extern void handleEvents();

    extern bool controller_shutdown();

    //extern bool dev_read_shutdown();

    //void control_ps5_features(SDL_GameController* controller, uint8 red, uint8 green, uint8 blue, uint8 left_trigger, uint8 right_trigger);


    //void assist_send_features();
    //void manual_send_features();
    //void manual_btns_simple();
    //void manual_btns();
    //void control_ps5_controller(SDL_GameController* controller, Uint8 red, Uint8 green, Uint8 blue, Uint8 left_trigger, Uint8 right_trigger);
    //void assist_send_btns();


}



#endif // GAMECONTROLLER_H