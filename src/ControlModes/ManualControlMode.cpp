#include "ControlModes/ManualControlMode.h"
//#include "/ManualControlMode.h"
#include "GameController.h"
#include "Common.h"
#include "Session.h"
#include "SessionControl.h"


#include "RadioTx.h"
#include "packets/Manual.h"
//#include "packets/packets.h"

//#include "CommonTools.h"
#include <iostream>

#include <cstdint>

inline int common_map(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}



/*
    Sends values of changing axises for manual control
*/
void ManualControlMode::processFeatures() {

        //int16_t throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read;
        int throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read;

        throttle_val_read = SDL_GameControllerGetAxis(globalGameController.controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);           // Throttle
        elevator_val_read = SDL_GameControllerGetAxis(globalGameController.controller, SDL_CONTROLLER_AXIS_LEFTY);           // Elevator
        rudder_val_read = SDL_GameControllerGetAxis(globalGameController.controller, SDL_CONTROLLER_AXIS_LEFTX); 
        int right_x = SDL_GameControllerGetAxis(globalGameController.controller, SDL_CONTROLLER_AXIS_RIGHTX);   // Roll 
        int right_y = SDL_GameControllerGetAxis(globalGameController.controller, SDL_CONTROLLER_AXIS_RIGHTY);   // Flap / Slat

        //int aileron_left = (common_map(right_x, -32768, 32767, 0, 180));
        //int aileron_right = (common_map(right_x, -32768, 32767, 180, 0));
        //int flap_deployment = (common_map(right_y, -32768, 32767, 0, 180));
        //aileron_val_left_read = static_cast<uint8_t>(common_constrain(aileron_left + flap_deployment, 0, 180));       // Left Flaperon
        //aileron_val_right_read = static_cast<uint8_t>(common_constrain(aileron_right + flap_deployment, 0, 180));       // Right Flaperon

        throttle_val_read = (common_map(throttle_val_read, 0, 32767, 0, 180));           // Throttle
        elevator_val_read = (common_map(elevator_val_read, -32768, 32767, 0, 180));           // Elevator
        rudder_val_read = (common_map(rudder_val_read, -32768, 32767, 0, 180));

        uint8_t aileron_left = (common_map(right_x, -32768, 32767, 0, 180));
        uint8_t aileron_right = (common_map(right_x, -32768, 32767, 180, 0));
        uint8_t flap_deployment = (common_map(right_y, -32768, 32767, 0, 180)); // +90 since unsigned
        //uint8_t flap_deployment = (common_map(right_y, -32768, 32767, -90, 90)); // +90 since unsigned
        

        aileron_val_left_read = aileron_left + flap_deployment - 90;       // Left Flaperon      // static_cast<uint8_t>
        aileron_val_right_read = aileron_right + flap_deployment - 90;       // Right Flaperon

        //ManualPacket manual_pkt('m', temp_reads, 0);
        //ManualPacket manual_pkt('m', throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read);
        //ManualPacket* manual_pkt = new ManualPacket('m', temp_reads, 0);

        //std::cout << "\n\nThrottle: " << throttle_val_read << std::endl;
        //std::cout << "Elevator: " << elevator_val_read << std::endl;
        //std::cout << "Rudder: " << rudder_val_read << std::endl;
        //std::cout << "Left Aileron: " << aileron_val_left_read << std::endl;
        //std::cout << "Right Aileron: " << aileron_val_right_read << std::endl;
        //std::cout << "Flap Deployment (-90): " << flap_deployment - 90 << std::endl << std::endl;

        ManualPacket* manual_pkt = new ManualPacket('m', throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read);
        sendToPlane(manual_pkt);


    //usleep(100);
    return;
}




/*
TODO:    (Manual) Processes bitmask of pressed buttons
*/
// uint32_t& mask
void ManualControlMode::processEvent(uint32_t mask) {
    switch (mask) {
        // (A)
        // Assist/Manual toggle
        case BTN_CROSS:
            std::cout << "Cross button pressed" << std::endl;
            //std::cout << "A button pressed" << std::endl;
            setControlMode(ControlMode::ASSIST);
            // Add more checks as needed in future
            // TODO: Taken out only for Dev & Testing purposes
            //if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::MANUAL) {
            //    Session::control_mode.store(ControlMode::ASSIST);  // Set control mode to ASSIST
            //    std::cout << "Control mode set to ASSIST" << std::endl;
            //}         

            // Send StatusPacket


            //send_feature('a', 1, 4);
            break;
        
        // (B)
        // Holding Pattern toggle
        case BTN_CIRCLE:
            std::cout << "Circle button pressed" << std::endl;
            setControlMode(ControlMode::HOLDING);
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

