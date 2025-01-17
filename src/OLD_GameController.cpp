
#include "GameController.h"
#include "Common.h"
#include "Session.h"
#include <iostream>

#include <thread>
#include <chrono>

//#include <SDL2/SDL.h>

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
uint32_t GameController::getButtonCombinationMask(SDL_GameController* controller) {
    uint32_t mask = 0;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) mask |= BTN_CROSS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) mask |= BTN_CIRCLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) mask |= BTN_SQUARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) mask |= BTN_TRIANGLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) mask |= BTN_L1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) mask |= BTN_R1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK)) mask |= BTN_L3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) mask |= BTN_R3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) mask |= BTN_SHARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) mask |= BTN_OPTIONS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE)) mask |= BTN_PS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_TOUCHPAD)) mask |= BTN_TOUCHPAD;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_MISC1)) mask |= BTN_MUTE;
    return mask;
}


uint32_t GameController::getButtonCombinationMask() {
    uint32_t mask = 0;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) mask |= BTN_CROSS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) mask |= BTN_CIRCLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) mask |= BTN_SQUARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) mask |= BTN_TRIANGLE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) mask |= BTN_L1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) mask |= BTN_R1;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK)) mask |= BTN_L3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) mask |= BTN_R3;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) mask |= BTN_SHARE;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) mask |= BTN_OPTIONS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE)) mask |= BTN_PS;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_TOUCHPAD)) mask |= BTN_TOUCHPAD;
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_MISC1)) mask |= BTN_MUTE;
    return mask;
}
*/




/*
    Processes bitmask of pressed buttons
*/

/*
void GameController::handleButtonCombinations(uint32_t& mask) {
    switch (mask) {

        // (A)
        // Assist/Manual toggle
        case BTN_CROSS:
            std::cout << "Cross button pressed" << std::endl;

            std::cout << "A button pressed" << std::endl;
            //send_feature('a', 1, 4);

            if (control_mode != ControlMode::ASSIST) {
                control_mode = ControlMode::ASSIST;  // Set control mode to ASSIST
                std::cout << "Control mode set to ASSIST" << std::endl;
            }
            else {
                control_mode = ControlMode::MANUAL;  // Set control mode to MANUAL
                std::cout << "Control mode set to MANUAL" << std::endl;
            }

            break;
        
        // (B)
        // Holding Pattern toggle
        case BTN_CIRCLE:
            std::cout << "Circle button pressed" << std::endl;
            break;
        
        // (X)
        // Throttle Lock toggle
        case BTN_SQUARE:
            std::cout << "Square button pressed" << std::endl;
            break;

        // (Y)
        // PID Calibration toggle
        case BTN_TRIANGLE:
            std::cout << "Triangle button pressed" << std::endl;
            break;

        // (Start)
        // (Start) Pair ATC & Plane
        case BTN_OPTIONS:
            std::cout << "Options button pressed" << std::endl;
            std::cout << "START button pressed" << std::endl;
            break;

        // (Back)
        //Capture Runway
        case BTN_SHARE:
            std::cout << "Share button pressed" << std::endl;
            std::cout << "BACK button pressed" << std::endl;
            break;

        // (Guide)
        //Return to Home
        case BTN_PS:
            std::cout << "PS button pressed" << std::endl;
            std::cout << "GUIDE button pressed" << std::endl;
            break;

        // (Left Bumper)
        // Rudder Left (5 degrees)
        case BTN_L1:
            std::cout << "L1 button pressed" << std::endl;
            std::cout << "LEFT BUMPER button pressed" << std::endl;
            break;

        // (Right Bumper)
        // Rudder Right (5 degrees)
        case BTN_R1:
            std::cout << "R1 button pressed" << std::endl;
            std::cout << "RIGHT BUMPER button pressed" << std::endl;
            break;

        // (Left Stick)
        // Throttle Lock toggle
        case BTN_L3:
            std::cout << "L3 button pressed" << std::endl;
            std::cout << "LEFT STICK button pressed" << std::endl;
            break;

        // (Right Stick)
        // Holding Pattern toggle
        case BTN_R3:
            std::cout << "R3 button pressed" << std::endl;
            std::cout << "RIGHT STICK button pressed" << std::endl;
            break;

        // (Start + Pause)
        // Flight Mode toggle
        case (BTN_SHARE | BTN_OPTIONS):
            std::cout << "Share + Options (Start + Back) combination pressed" << std::endl;
            // Handle the Start + Back combination
            break;

        //// (LB + RB)
        //case (BTN_L1 | BTN_R1):
        //    std::cout << "L1 + R1 combination pressed" << std::endl;
        //    break;
        //// (LT + RT)
        //case (BTN_L2 | BTN_R2):
        //    std::cout << "L2 + R2 combination pressed" << std::endl;
        //    break;
        // (Mute)
        //case BTN_MUTE:
        //    std::cout << "Mute button pressed" << std::endl;
        //    break;
        // (Touchpad)
        //case BTN_TOUCHPAD:
        //    std::cout << "Touchpad button pressed" << std::endl;
        //    break;

        default:
            std::cout << "Unknown button combination" << std::endl;
            break;

    }
}

*/


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
            
            // Wait for q to be pressed then quit the program
            
            //char c;
            ////std::cout << "Press q to quit" << std::endl;
            //std::cin >> c;
            //if (c == 'q') {
            //    return false;
            //}
            
        }
        std::cout << "While loop broke" << std::endl;

    } else {
        controller = SDL_GameControllerOpen(0);
        if (controller == nullptr) {
            std::cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;

            
            //// Wait for q to be pressed then quit the program
            //char c;
            ////std::cout << "Press q to quit" << std::endl;
            //std::cin >> c;
            //if (c == 'q') {
            //    return false;
            //}
            
        }
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }
    return true;
}
*/


bool GameController::waitForConnection(){
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

    return true;
}

bool GameController::controller_setup() {
    // Initialize controller
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GameControllerEventState(SDL_ENABLE);

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


