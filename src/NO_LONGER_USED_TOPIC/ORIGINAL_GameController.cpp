
#include "GameController.h"
#include "Common.h"
#include "Session.h"

//#include "common.h"
//#include "session.h"
//#include "atc.h"
//#include <SDL2/SDL.h>
//#include "atc_rf.h"


//using namespace GameController;

// GameController::

//SDL_GameController* controller = nullptr;
GameController::controller_defaults = {0, 0, 0, 0, 0};
GameController::controller = nullptr;
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
    buttonMask = 0;
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



bool GameController::controller_setup() {
    // Initialize controller
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    //controller = SDL_GameControllerOpen(0);
    //if (controller == nullptr) {
    //    return false;
    //}
    //return true;


    if (SDL_NumJoysticks() < 1) {
    //if //(NumGameControllers() < 1) {
        std::cout << "Warning: No joysticks connected!" << std::endl;
        while(SDL_NumJoysticks() < 1){
            usleep(10000);
            std::cout << "Warning: No joysticks connected!" << std::endl;
            
            // Wait for q to be pressed then quit the program
            char c;
            //std::cout << "Press q to quit" << std::endl;
            std::cin >> c;
            if (c == 'q') {
                return false;
            }
        }
        std::cout << "While loop broke" << std::endl;

    } else {
        controller = SDL_GameControllerOpen(0);
        if (controller == nullptr) {
            std::cerr << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;
            // Wait for q to be pressed then quit the program
            char c;
            //std::cout << "Press q to quit" << std::endl;
            std::cin >> c;
            if (c == 'q') {
                return false;
            }
        }
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }


    return true
}

/*
    Control LEDs, Resistance, and Vibration
*/
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




/*
TODO: Implement , copy from manual_send_features
*/
// Sends values of changing axises and buttons, sends -1 for default_cruise
void GameController::assist_send_features() {
    if (controller) {

        // 1 Check for changes , update no changes to -1

        // 2 

        //uint8_t temp_throttle_val, temp_elevator_val, temp_rudder_val, temp_aileron_left_val, temp_aileron_right_val;
        //uint8_t temp_vals[NUM_FEATS] = {&temp_throttle_val, &temp_elevator_val, &temp_rudder_val, &temp_aileron_left_val, &temp_aileron_right_val };

        uint8_t throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read;
        uint8_t temp_reads[NUM_FEATS] = {&throttle_val_read, &elevator_val_read, &rudder_val_read, &aileron_val_left_read, &aileron_val_right_read };

        //uint8_t send_vals[NUM_FEATS] = {-1, -1, -1, -1, -1};

       // feat_vals[0] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);          // Throttle 

        

        throttle_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT), -511, 512, 0, 180);           // Throttle
        elevator_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY), -511, 512, 0, 180);           // Elevator
        rudder_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX), -511, 512, 0, 180);           // Rudder
        aileron_val_left_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX), -511, 512, 0, 180);           // Left Aileron
        aileron_val_right_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX), -511, 512, 0, 180);           // Right Aileron








        //temp_throttle_val = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT), -511, 512, 0, 180);           // Throttle
        //send_mp_feature('p', (uint8_t)feat_vals[i], i);
        //usleep(10000);

        /*
        // (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);   
        //if ( abs((int)temp_throttle_val - (int)throttle_val) >= 2)
        if ( abs((int)temp_throttle_val - 0) >= 2)
            throttle_val = temp_throttle_val;
        else  
            temp_throttle_val = -1;
        */



        //temp_vals[1] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);           // Elevator
        temp_elevator_val = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY), -511, 512, 0, 180);
        //if ( abs((int)temp_elevator_val - (int)elevator_val) >= 2)
        if ( abs((int)temp_elevator_val - 90) >= 2)          // If elevator input is not at neutral
            elevator_val = temp_elevator_val;
        else  
/* TODO: Implement a ground-based PID controller*/
            // pi_pid.h , use a ground based PID controller from values trained with the plane PID
                // OR use a ground-based PID autotuning system that can be more advanced
            temp_elevator_val = -1;

        //feat_vals[2] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);           // Rudder
        temp_rudder_val = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX), -511, 512, 0, 180);
        if ( abs((int)temp_rudder_val - (int)rudder_val) >= 2)
            rudder_val = temp_rudder_val;
        else
            temp_rudder_val = -1;



        // Right Stick (-511 to 512) -> (0 to 180)   // Default (90,90) or (0,0) on controller
        uint8_t x = (uint8_t)map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX), -511, 512, 0, 180);   // Roll 
        uint8_t y = (uint8_t)map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY), -511, 512, 0, 180);   // Flap / Slat
        temp_aileron_left_val = 90 + y;     // Left Aileron (Flaperon/Slat)
        temp_aileron_right_val = 90 - x;    // Right Aileron (Flaperon/Slat)


        //uint8_t roll_axis = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);           // Roll
        //uint8_t roll_axis = (uint8_t)map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX), -511, 512, -90, 90);           // RollSDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);           // Roll
        

        //int16_t mapped_value = (roll_input * 90) / 512;

        //feat_vals[3] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);           // Left Aileron
        //feat_vals[4] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);    // Right Aileron


        //feat_vals[3] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);           // Left Aileron
        //feat_vals[4] = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);    // Right Aileron




        //for (int i = 0; i < NUM_FEATS; i++) {
        //    send_mp('a', (uint8_t)temp_vals[i], i);         // assist
        //    usleep(10000);
        //}
        send_mp('a', temp_vals);         // assist


        //for (int i = 0; i < NUM_FEATS; i++) {
        //    send_feature('p', (int)feat_vals[i], i);
        //    usleep(10000);
        //}

    }
}



/*
TODO:    (Manual) Processes bitmask of pressed buttons
*/
void GameController::OLD_handleManualButtonCombinations(uint32_t& mask) {
    switch (mask) {

        // (A)
        // Assist/Manual toggle
        case BTN_CROSS:
            std::cout << "Cross button pressed" << std::endl;

            std::cout << "A button pressed" << std::endl;

    

            //send_feature('a', 1, 4);

            if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::ASSIST) {
                Session::control_mode.store(ControlMode::MANUAL);  // Set control mode to ASSIST
                std::cout << "Control mode set to MANUAL" << std::endl;
            }
            else {
                control_mode.store(ControlMode::MANUAL);  // Set control mode to MANUAL
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


/*
TODO:    (Assist) Processes bitmask of pressed buttons
*/
void GameController::handleAssistButtonCombinations(uint32_t& mask) {
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




/*
TODO: Delete after testing
*/

void GameController::manual_btns_simple() {
    if (controller) {

        // Assist/Manual toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
            std::cout << "A button pressed" << std::endl;
            //send_feature('a', 1, 4);

            if (control_mode != ASSIST) {
                control_mode = ASSIST;  // Set control mode to ASSIST
                std::cout << "Control mode set to ASSIST" << std::endl;
            }
            else {
                control_mode = MANUAL;  // Set control mode to MANUAL
                std::cout << "Control mode set to MANUAL" << std::endl;
            }
        }

        // Holding Pattern toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
            std::cout << "B button pressed" << std::endl;
            //send_feature('b', 2, 4);
        }

        // Throttle Lock toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) {
            std::cout << "X button pressed" << std::endl;
            //send_feature('x', 3, 4);
        }

        // Pair ATC & Plane
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
            std::cout << "START button pressed" << std::endl;
            //send_feature('c', 100, 4);
        }


/*
        // PID Calibration toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) {
            std::cout << "Y button pressed" << std::endl;
            //send_feature('y', 4, 4);
        }

        // Capture Runway
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) {
            std::cout << "BACK button pressed" << std::endl;
            //send_feature('a', 101, 4);
        }

        // Return to Home
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE)) {
            std::cout << "GUIDE button pressed" << std::endl;
            //send_feature('g', 102, 4);
        }

        // Rudder Left (5 degrees)
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
            std::cout << "LEFT BUMPER button pressed" << std::endl;
            //send_feature('l', 103, 4);
        }

        // Rudder Right (5 degrees)
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
            std::cout << "RIGHT BUMPER button pressed" << std::endl;
            //send_feature('r', 104, 4);
        }
*/
        
        // Thottle Lock toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK)) {
            std::cout << "LEFT STICK button pressed" << std::endl;
            //send_feature('s', 105, 4);
        }

        // Holding Pattern toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) {
            std::cout << "RIGHT STICK button pressed" << std::endl;
            //send_feature('t', 106, 4);
        }
        usleep(10000);
    }
}


/*
REPLACED by handleButtonCombinations
*/
void GameController::manual_btns() {
        // Assist/Manual toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
            std::cout << "A button pressed" << std::endl;
            //send_feature('a', 1, 4);

            //if (Session::control_mode != ControlMode::ASSIST) {
            if (Session::control_mode.load(std::memory_order_relaxed) != ControlMode::ASSIST) {
                //Session::control_mode = ControlMode::ASSIST;  // Set control mode to ASSIST
                Session::control_mode.store(ControlMode::ASSIST, std::memory_order_release);
                std::cout << "Control mode set to ASSIST" << std::endl;
            }
            else {
                //Session::control_mode = Session::MANUAL;  // Set control mode to MANUAL
                Session::control_mode.store(ControlMode::MANUAL, std::memory_order_release);
                std::cout << "Control mode set to MANUAL" << std::endl;
            }


        }

        // Holding Pattern toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
            std::cout << "B button pressed" << std::endl;
            //send_feature('b', 2, 4);
        }

        // Throttle Lock toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) {
            std::cout << "X button pressed" << std::endl;
            //send_feature('x', 3, 4);
        }

        // Pair ATC & Plane
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
            std::cout << "START button pressed" << std::endl;
            //send_feature('c', 100, 4);
        }


/*
        // PID Calibration toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) {
            std::cout << "Y button pressed" << std::endl;
            //send_feature('y', 4, 4);
        }

        // Capture Runway
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) {
            std::cout << "BACK button pressed" << std::endl;
            //send_feature('a', 101, 4);
        }

        // Return to Home
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE)) {
            std::cout << "GUIDE button pressed" << std::endl;
            //send_feature('g', 102, 4);
        }

        // Rudder Left (5 degrees)
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
            std::cout << "LEFT BUMPER button pressed" << std::endl;
            //send_feature('l', 103, 4);
        }

        // Rudder Right (5 degrees)
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
            std::cout << "RIGHT BUMPER button pressed" << std::endl;
            //send_feature('r', 104, 4);
        }
*/
        
        // Thottle Lock toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK)) {
            std::cout << "LEFT STICK button pressed" << std::endl;
            //send_feature('s', 105, 4);
        }

        // Holding Pattern toggle
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) {
            std::cout << "RIGHT STICK button pressed" << std::endl;
            //send_feature('t', 106, 4);
        }
        usleep(1000);
    
}




/*
TODO: Emergency, Shits n gigs
*/
void GameController::control_ps5_controller(SDL_GameController* controller, Uint8 red, Uint8 green, Uint8 blue, Uint8 left_trigger, Uint8 right_trigger) {
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


/*
TODO: Implement , copy from manual_send_btns
*/
void GameController::assist_send_btns() {
    if (controller) {


        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
            std::cout << "START button pressed" << std::endl;
            send_feature('c', 100, 4);
            usleep(10000);
        }

        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) {
            std::cout << "BACK button pressed" << std::endl;
            send_feature('a', 101, 4);
            usleep(10000);
        }
    }  

}


/*
TODO: Implement , sqlite3 wrapper
*/
/*
inline bool sql_log(const char table, const char field, int value) {
    return true;
}
*/

































