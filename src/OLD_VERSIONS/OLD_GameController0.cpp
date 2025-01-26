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

GameController::GameController() {
    //this->featureFunction = this->waiting;
    //this->buttonFunction = PairingControlMode::send_btns;
}
GameController::GameController(uint8_t controller_id) {
    this->controller_id = controller_id;
    //this->featureFunction = this->waiting;
    //this->buttonFunction = PairingControlMode::send_btns;
}

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

//uint32_t GameController::getButtons() {
//    return buttons.exchange(NULL_BUTTONS, std::memory_order_release);
//}




//static GameController& getInstance() {
//        static GameController instance;
//        return instance;
//}





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

bool GameController::stop() {
    Session::ctlr_loop_active.store(false, std::memory_order_release);
    if (controller_shutdown()) {
        std::cout << "Controller shutdown returned" << std::endl;
        controller_thread.join();
        std::cout << "Controller thread 0 joined" << std::endl;
        event_thread.join();
        std::cout << "Controller thread 1 joined" << std::endl;
        return true;
    }
    return false;
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

// TODO: Delete
/*
void GameController::waiting() {
    ControlMode mode = Session::control_mode.load(std::memory_order_relaxed);
    while (mode != ControlMode::MANUAL 
        && mode != ControlMode::ASSIST
        && mode != ControlMode::TAXI)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } // Wait for an appropriate control mode    
    
    switch (Session::control_mode.load(std::memory_order_relaxed)) {
       // 8 Modes total, 5 fully-automated, 3 user-required
       case ControlMode::MANUAL:
          featureFunction = ManualControlMode::manualMode;
           break;
       case ControlMode::ASSIST:
          featureFunction = AssistControlMode::assistMode;
           break;
       case ControlMode::TAXI:
          featureFunction = TaxiControlMode::taxiMode;
           break;
        default:
          featureFunction = waiting;
           break;
    }
}
*/


// TODO: Implement pause, only enable in these modes    // TODO: Go back to switch-case if errors
void GameController::loop() {
    while (Session::ctlr_loop_active.load(std::memory_order_relaxed)
    && !Session::quit_flag.load(std::memory_order_relaxed))  {

        ControlMode mode = Session::control_mode.load(std::memory_order_relaxed);
        while (mode != ControlMode::MANUAL 
            && mode != ControlMode::ASSIST
            && mode != ControlMode::TAXI
            || Session::ctlr_paired.load(std::memory_order_relaxed) == false
            && Session::ctlr_loop_active.load(std::memory_order_relaxed)
            && !Session::quit_flag.load(std::memory_order_relaxed) ) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } // Wait for an appropriate control mode    

        switch (Session::control_mode.load(std::memory_order_relaxed)) {
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
        continue;
    }
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

/*
bool GameController::waitForConnection(){
    while (Session::ctlr_paired.load(std::memory_order_relaxed) == false) {
        if (Session::quit_flag.load(std::memory_order_acquire)) {
            return false;
        }

        for (int i = 0; i < SDL_NumJoysticks(); ++i) {
            if (SDL_IsGameController(i)) {
                controller = SDL_GameControllerOpen(i);
                if (controller != nullptr) {
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


    
    //if (SDL_NumJoysticks() < 1) {
    ////if //(NumGameControllers() < 1) {
    //    std::cout << "Warning: No joysticks connected!" << std::endl;
    //    std::cout << "Waiting for controller..." << std::endl;
    //    while(SDL_NumJoysticks() < 1){
    //        //usleep(10000);
    //        std::this_thread::sleep_for(std::chrono::milliseconds(5000));    // Wait 5 seconds
    //        if (Session::quit_flag.load(std::memory_order_acquire)) {
    //            return false;
    //        }
    //        std::cout << "Warning: No joysticks connected! (retry)" << std::endl;
    //        continue;
    //    }
    //    std::cout << "While loop broke" << std::endl;

    //} else {
    //    controller = SDL_GameControllerOpen(0);
    //    if (controller == nullptr) {
    //        std::cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;
    //    }
    //    std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    //}
    

    return true;
}


bool GameController::controller_setup() {
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
*/

// Return true -> controller shutdown successfully
bool GameController::controller_shutdown() {
    Session::ctlr_shtdwn.store(true, std::memory_order_release);
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
    std::cout << "Controller shutdown finished" << std::endl;
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
    while (Session::ctlr_loop_active.load(std::memory_order_relaxed)
    && !Session::quit_flag.load(std::memory_order_relaxed)) {
            
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
                            //std::cout << "Controller connected" << std::endl;
                            std::cout << "Found game controller: " << SDL_GameControllerName(controller) << std::endl;
                            Session::ctlr_paired.store(true, std::memory_order_release);
                            Logging::insertEventLog(EventType::CONTROLLER_CONNECTED);
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

                //case SDL_CONTROLLERBUTTONDOWN:
                //{
                //    uint32_t pressedButtons = 0;
                //    SDL_Event event;
                //    bool buttonReleased = false;
                //    //pressedButtons |= (1 << e.cbutton.button);
                //    while (!buttonReleased) {
                //        while (SDL_PollEvent(&event)) {
                //            switch (event.type) {
                //                case SDL_CONTROLLERBUTTONDOWN:
                //                    pressedButtons |= (1 << event.cbutton.button);
                //                    break;
                //                case SDL_CONTROLLERBUTTONUP:
                //                    buttonReleased = true;
                //                    break;
                //            }
                //        }
                //        SDL_Delay(10); // Small delay to avoid busy-waiting
                //    }
                //    processEvent(pressedButtons);
                //}
                //    break;


                //case SDL_CONTROLLERBUTTONUP:
                //    break;
                default:
                    break;

                

            }
        }
        SDL_Delay(2);  // Avoid busy-waiting
    }
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


