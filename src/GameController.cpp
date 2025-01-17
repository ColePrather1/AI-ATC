
#include "GameController.h"
#include "Common.h"
#include "Session.h"
#include <iostream>

#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

//#include "common.h"
//#include "session.h"
//#include "atc.h"
//#include <SDL2/SDL.h>
//#include "atc_rf.h"

//GameController::controller = SDL_GameController*(nullptr);

//using namespace GameController;

// GameController::

//SDL_GameController* controller = nullptr;
//GameController::controller_defaults = {0, 0, 0, 0, 0};

//uint8_t 
//extern uint8_t controller_defaults = {0, 90, 90, 90, 90};
//uble plane_default_cruise = {0,0,0,0,0,0};

//void calibrate_controller() {
//    controller_defaults[0] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
//    controller_defaults[1] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
//    controller_defaults[2] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
//    controller_defaults[3] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
//}


/*
bool isDefault(uint8_t val) {}
*/


/*
    Creates bitmask of pressed buttons
*/

void GameController::getButtonCombinationMask() {
    GameController::buttonMask = 0;
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
}




/*
bool GameController::tryConnect(){
    if (SDL_NumJoysticks() < 1) {
    //if //(NumGameControllers() < 1) {
        std::cout << "Warning: No joysticks connected!" << std::endl;
        std::cout << "Waiting for controller..." << std::endl;
        while(SDL_NumJoysticks() < 1){
            //usleep(10000);
            this_thread::sleep_for(std::chrono::milliseconds(5000));    // Wait 5 seconds
            if (Session::quit_flag.load(std::memory_order_acquire)) {
                return false;
            }
            std::cout << "Warning: No joysticks connected!" << std::endl;
            continue;
            //std::cout << "Warning: No joysticks connected!" << std::endl;
            
        }
        std::cout << "While loop broke" << std::endl;

    } else {
        controller = SDL_GameControllerOpen(0);
        if (controller == nullptr) {
            std::cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;
            
        }
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }
    return true;
}
*/


bool GameController::waitForConnection(){


    while (Session::ctlr_paired.load(std::memory_order_relaxed) == false) {
        if (Session::quit_flag.load(std::memory_order_acquire)) {
            return false;
        }

        for (int i = 0; i < SDL_NumJoysticks(); ++i) {
            if (SDL_IsGameController(i)) {
                controller = SDL_GameControllerOpen(i);
                if (controller) {
                    std::cout << "Found game controller: " << SDL_GameControllerName(controller) << std::endl;
                    Session::ctlr_paired.store(true, std::memory_order_release);
                    // TODO: Implement ctrl_paired SQL logging event 
                    break;
                }
                else {
                    std::cout << "Unable to open game controller: " << SDL_GetError() << std::endl;
                    continue;
                }
            }
        }
        std::cout << "Waiting for controller..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));    // Wait 5 seconds
        continue;
    }


    /*
    if (SDL_NumJoysticks() < 1) {
    //if //(NumGameControllers() < 1) {
        std::cout << "Warning: No joysticks connected!" << std::endl;
        std::cout << "Waiting for controller..." << std::endl;
        while(SDL_NumJoysticks() < 1){
            //usleep(10000);
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));    // Wait 5 seconds
            if (Session::quit_flag.load(std::memory_order_acquire)) {
                return false;
            }
            std::cout << "Warning: No joysticks connected! (retry)" << std::endl;
            continue;
        }
        std::cout << "While loop broke" << std::endl;

    } else {
        controller = SDL_GameControllerOpen(0);
        if (controller == nullptr) {
            std::cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;
        }
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }
    */

    return true;
}

bool GameController::controller_setup() {
    // Initialize controller
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GameControllerEventState(SDL_ENABLE);
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5, "1");


    //controller = SDL_GameControllerOpen(0);
    //if (controller == nullptr) {
    //    return false;
    //}
    //return true;


    if (waitForConnection()) {
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }
    else {
        std::cout << "Controller failed to connect. Ending program" << std::endl;
        return false;
    }


    return true;
}


// Return true -> controller shutdown successfully
bool GameController::controller_shutdown() {
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
    std::cout << "Controller shutdown finished" << std::endl;
    return true;
}

// Return true -> shutdown program
void GameController::handleEvents() {
    SDL_Event e;
    //int it = 0;
    if(SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q) {
                    Session::quit_flag.store(true, std::memory_order_release);
                }
                break;
            case SDL_QUIT:
                Session::quit_flag.store(true, std::memory_order_release);
                break;
            case SDL_CONTROLLERDEVICEADDED:
                if (!controller) {
                    controller = SDL_GameControllerOpen(e.cdevice.which);
                    if (controller) {
                        std::cout << "Controller connected" << std::endl;
                    }
                }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                if (controller && e.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller))) {
                    SDL_GameControllerClose(controller);
                    controller = nullptr;
                    std::cout << "Controller disconnected" << std::endl;
                }
                break;
            default:
                break;
        }
        //it++;

        if (!controller) {
            for (int i = 0; i < SDL_NumJoysticks(); ++i) {
                if (SDL_IsGameController(i)) {
                    controller = SDL_GameControllerOpen(i);
                    if (controller) {
                        std::cout << "Controller reconnected" << std::endl;
                        break;
                    }
                }
            }
        }
        SDL_Delay(100);  // Avoid busy-waiting
    }

    return;
}

/*
void GameController::handleEvents() {
    SDL_Event e;
    int it = 0;
    while (SDL_PollEvent(&e) != 0 && it < 10) {
        switch (e.type) {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q) {
                    Session::quit_flag.store(true, std::memory_order_release);
                }
                break;
            case SDL_QUIT:
                Session::quit_flag.store(true, std::memory_order_release);
                break;
            case SDL_CONTROLLERDEVICEADDED:
                if (!controller) {
                    controller = SDL_GameControllerOpen(event.cdevice.which);
                    if (controller) {
                        std::cout << "Controller connected" << std::endl;
                    }
                }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                if (controller && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller))) {
                    SDL_GameControllerClose(controller);
                    controller = nullptr;
                    std::cout << "Controller disconnected" << std::endl;
                }
                break;
            default:
                break;
        }
        it++;
    }

    return false;
}
*/



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


