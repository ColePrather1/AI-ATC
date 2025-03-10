#include <iostream>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include <cstdint>

#include "GameController.h"
#include "ControlModes/ControlModes.h"
#include "Common.h"
#include "Session.h"
#include "Logging.h"
#include <bitset>

GameController::GameController() {}

GameController::GameController(uint8_t controller_id) {
    this->controller_id = controller_id;
}


//void calibrate_controller() {
//    controller_defaults[0] = (int16_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
//    controller_defaults[1] = (int16_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
//    controller_defaults[2] = (int16_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
//    controller_defaults[3] = (int16_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
//}



// Creates bitmask of pressed buttons
uint32_t GameController::getButtonCombinationMask() {
    uint32_t buttonMask = 0;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) buttonMask |= BTN_CROSS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) buttonMask |= BTN_CIRCLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) buttonMask |= BTN_SQUARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) buttonMask |= BTN_TRIANGLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) buttonMask |= BTN_L1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) buttonMask |= BTN_R1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK)) buttonMask |= BTN_L3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) buttonMask |= BTN_R3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) buttonMask |= BTN_SHARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) buttonMask |= BTN_OPTIONS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE)) buttonMask |= BTN_PS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_TOUCHPAD)) buttonMask |= BTN_TOUCHPAD;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_MISC1)) buttonMask |= BTN_MUTE;

    return buttonMask;
}

// Returns true if successful
bool GameController::start() {
    if (!setup()) {
        return false;
    }
    std::cout << "GameController setup complete." << std::endl;
    Session::ctlr_loop_active.store(true, std::memory_order_release);
    event_thread = std::thread(&GameController::handleEvents, this);
    controller_thread = std::thread(&GameController::loop, this);

    return true;
}

// Returns true if successful
bool GameController::stop() {
    if (controller_shutdown()) {
        std::cout << "Controller shutdown finished" << std::endl;
    }
    return true;
}

bool GameController::setup() {
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI, "1");
    // Initialize controller
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {       // SDL_INIT_JOYSTICK | 
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "1");
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5, "1");
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE, "1");
    SDL_GameControllerEventState(SDL_ENABLE);

    return true;
}

// TODO: Implement pause, only enable in these modes
// TODO: Redo this
void GameController::loop() {
    features_active.store(true, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    while (features_active.load(std::memory_order_relaxed)
    && !Session::quit_flag.load(std::memory_order_relaxed))  {
        ControlMode mode = Session::control_mode.load(std::memory_order_relaxed);
        while ( (mode != ControlMode::MANUAL && mode != ControlMode::ASSIST && mode != ControlMode::TAXI)   // While control mode is not appropriate
            && features_active.load(std::memory_order_relaxed)                                              // While parent loop is active          
            && !Session::quit_flag.load(std::memory_order_relaxed) )                                        // While quit_flag is false (i.e. program running)
        {
            mode = Session::control_mode.load(std::memory_order_relaxed);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } // Wait for an appropriate control mode    


        switch (mode) {
           // 8 Modes total, 5 fully-automated, 3 user-required
           case ControlMode::MANUAL:
              ManualControlMode::processFeatures();
               break;
           case ControlMode::ASSIST:
              AssistControlMode::processFeatures();
               break;
           case ControlMode::TAXI:
              TaxiControlMode::processFeatures();
               break;
            default:
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
               break;
        }   
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));     // Slow down a bit, 20Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(500));     // Slow packets to testing receiver
        continue;
    }
    features_active.store(false, std::memory_order_release);
    features_finished.store(true, std::memory_order_release);
    return;
}


// TODO: replace switch-case of ControlMode to be s-c of ButtonCombo
/*
void GameController::handleButtons(uint32_t& buttonMask) {
    switch (Session::control_mode.load(std::memory_order_relaxed)) {
        case ControlMode::MANUAL:
           ManualControlMode::manualMode(buttonMask);
            break;
        case ControlMode::ASSIST:
           AssistControlMode::assistMode(buttonMask);
            break;
        case ControlMode::AUTO:
           AutoControlMode::autoMode(buttonMask);
            break;
        case ControlMode::EMERGENCY:
           EmergencyControlMode::emergencyMode(buttonMask);
            break;
        case ControlMode::HOLDING:
           HoldingControlMode::holdingMode(buttonMask);
            break;
        case ControlMode::TAXI:
           TaxiControlMode::taxiMode(buttonMask);
            break;
        case ControlMode::PAIRING:
           PairingControlMode::pairingMode(buttonMask);
            break;
        case ControlMode::RECOVERY:
           RecoveryControlMode::recoveryMode(buttonMask);
            break;
        default:
            break;
    }
}
*/


// Return true -> controller shutdown successfully
bool GameController::controller_shutdown() {
    Session::ctlr_shtdwn.store(true, std::memory_order_release);
    //Session::ctlr_loop_active.store(false, std::memory_order_release);
    events_active.store(false, std::memory_order_release);
    features_active.store(false, std::memory_order_release);

    //std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //std::cout << "Controller shutdown returned" << std::endl;

    while (!events_finished.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (event_thread.joinable()){
        event_thread.join();
        //std::cout << "Controller thread 1 joined" << std::endl;
    }
    else {
        std::cout << "Controller event thread not joinable" << std::endl;
    }
    
    //std::cout << "prior to thread 1 wait" << std::endl;
    while (!features_finished.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    //std:: cout << "prior to thread 0 joinable check" << std::endl;    
    if (controller_thread.joinable()){
        //std::cout << "prior to thread 0 join" << std::endl;
        controller_thread.join();
        //std::cout << "Controller thread 0 joined" << std::endl;
    }
    else {
        std::cout << "Controller features thread not joinable" << std::endl;
    }

    if (controller) {
        SDL_GameControllerClose(controller);
        controller = nullptr;
    }
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    //SDL_Quit();

   // Check if any other SDL subsystems are still active
    if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0) {
        SDL_Quit();
    }
    Session::ctlr_shtdwn.store(false, std::memory_order_release);
    Session::ctlr_loop_active.store(false, std::memory_order_release);
    return true;
}



void GameController::processEvent(uint32_t& buttonMask) {
    switch (Session::control_mode.load(std::memory_order_relaxed)) {
        case ControlMode::MANUAL:
           ManualControlMode::processEvent(buttonMask);
            break;
        case ControlMode::ASSIST:
           AssistControlMode::processEvent(buttonMask);
            break;
        case ControlMode::AUTO:
           AutoControlMode::processEvent(buttonMask);
            break;
        case ControlMode::EMERGENCY:
           EmergencyControlMode::processEvent(buttonMask);
            break;
        case ControlMode::HOLDING:
           HoldingControlMode::processEvent(buttonMask);
            break;
        case ControlMode::TAXI:
           TaxiControlMode::processEvent(buttonMask);
            break;
        case ControlMode::PAIRING:
           PairingControlMode::processEvent(buttonMask);
            break;
        case ControlMode::RECOVERY:
           RecoveryControlMode::processEvent(buttonMask);
            break;
        default:
            break;
    }

    return;
}


void GameController::handleEvents() {
    events_active.store(true, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    while (events_active.load(std::memory_order_relaxed)
    && !Session::quit_flag.load(std::memory_order_relaxed)) {
            
        SDL_Event e;
        //int it = 0;
        if(SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    //if (e.key.keysym.sym == SDLK_q) {
                    //    Session::quit_flag.store(true, std::memory_order_release);
                    //}
                    //break;
                case SDL_QUIT:
                    //Session::quit_flag.store(true, std::memory_order_release);    // SDL2 does not tell us when to quit
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    if (!controller) {
                        controller = SDL_GameControllerOpen(e.cdevice.which);
                        if (controller) {
                            std::cout << "Found game controller: " << SDL_GameControllerName(controller) << std::endl;
                            Session::ctlr_paired.store(true, std::memory_order_release);
                            Logging::insertEventLog(EventType::CONTROLLER_CONNECTED);
                            //std::cout << "Controller connected" << std::endl;
                        }
                    }
                    break;
                case SDL_CONTROLLERDEVICEREMOVED:
                    if (controller && e.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller))) {
                        SDL_GameControllerClose(controller);
                        controller = nullptr;
                        std::cout << "Controller disconnected" << std::endl;
                        Session::ctlr_paired.store(false, std::memory_order_release);
                        Logging::insertEventLog(EventType::CONTROLLER_DISCONNECTED);
                    }
                    break;

                // TODO: implement getButtonCombinationMask() to keep track of all pressed buttons
                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_CONTROLLERBUTTONUP:
                    {
                        uint32_t pressedButtons = 0;
                        SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(e.cbutton.button);
                        
                        if (e.type == SDL_CONTROLLERBUTTONDOWN) {
                            pressedButtons |= (1 << button);
                        } else {
                            pressedButtons &= ~(1 << button);
                        }
                        processEvent(pressedButtons);
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(2);  // Avoid busy-waiting
        continue;
    }
    events_active.store(false, std::memory_order_release);
    events_finished.store(true, std::memory_order_release);
    return;
}





/*
    Control LEDs, Resistance, and Vibration
*/

/*
void GameController::control_ps5_features(SDL_GameController* controller, Uint8 red, Uint8 green, Uint8 blue, Uint8 left_trigger, Uint8 right_trigger) {
    if (controller) {
        // Set LED color
        SDL_GameControllerSetLED(controller, red, green, blue);
        
        // Set trigger effects (Resitance)
        //SDL_GameControllerSetTriggerEffect(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT, left_trigger);
        //SDL_GameControllerSetTriggerEffect(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, right_trigger);
        
        // Set vibration
        SDL_GameControllerRumble(controller, 0xFFFF, 0xFFFF, 100);
    }
}
*/


