#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <thread>
#include <functional>
#include <atomic>

// PS5 Define button masks for SDL2 DualSense controller
#define BTN_CROSS    (1 << 0)
#define BTN_CIRCLE   (1 << 1)
#define BTN_SQUARE   (1 << 2)
#define BTN_TRIANGLE (1 << 3)
#define BTN_L1       (1 << 9)
#define BTN_R1       (1 << 10)
#define BTN_L2       (1 << 4)
#define BTN_R2       (1 << 5)
#define BTN_SHARE    (1 << 4)
#define BTN_OPTIONS  (1 << 6)
#define BTN_L3       (1 << 7)
#define BTN_R3       (1 << 8)
#define BTN_PS       (1 << 12)
#define BTN_TOUCHPAD (1 << 13)
#define BTN_MUTE     (1 << 14)

constexpr uint32_t NULL_BUTTONS = 0;

class GameController {
public:

    uint8_t controller_id;
    SDL_GameController* controller;
    std::atomic<bool> features_active{false};
    std::atomic<bool> events_active{false};
    std::atomic<bool> features_finished{false};
    std::atomic<bool> events_finished{false};
    std::thread controller_thread;
    std::thread event_thread;

    bool start();
    bool stop();
    bool setup();
    void loop();
    
    uint32_t getButtonCombinationMask();
    uint32_t getFeatures();

    void handleEvents();
    void processEvent(uint32_t& buttonMask);
    bool controller_shutdown();

    GameController();
    GameController(uint8_t controller_id);
    ~GameController() {}
};

inline GameController globalGameController{static_cast<uint8_t>(0)};


#endif // GAMECONTROLLER_H