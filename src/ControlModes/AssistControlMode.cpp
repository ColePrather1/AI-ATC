#include "ManualControlMode.h"
#include "GameController.h"


/*
TODO: Test Right X-Y Methods with wings attached
*/


void ManualControlMode::assistMode() {

    // Sticks & Triggers
    assist_send_features();


    // Buttons 
    assist_send_btns();


    // System checks to act on buttons



}

/*
    Sends values of changing axises for manual control
*/
void ManualControlMode::manual_send_features() {

        uint8_t throttle_val_read, elevator_val_read, rudder_val_read, aileron_val_left_read, aileron_val_right_read;
        uint8_t temp_reads[NUM_FEATS] = {&throttle_val_read, &elevator_val_read, &rudder_val_read, &aileron_val_left_read, &aileron_val_right_read };

        throttle_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT), -511, 512, 0, 180);           // Throttle
        elevator_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY), -511, 512, 0, 180);           // Elevator
        rudder_val_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX), -511, 512, 0, 180);           // Rudder
        //aileron_val_left_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX), -511, 512, 0, 180);           // Left Aileron
        //aileron_val_right_read = map(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX), -511, 512, 0, 180);           // Right Aileron

        uint8_t right_x = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);   // Roll 
        uint8_t right_y = (uint8_t)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);   // Flap / Slat
        uint8_t aileron_left = (uint8_t)map(right_x, -512, 512, 0, 180);
        uint8_t aileron_right = (uint8_t)map(right_x, -512, 512, 180, 0);
        uint8_t flap_deployment = (uint8_t)map(right_y, -512, 512, 0, 180);
        aileron_val_left_read = constrain(aileron_left + flap_deployment, 0, 180);       // Left Flaperon
        aileron_val_right_read = constrain(aileron_right + flap_deployment, 0, 180);       // Right Flaperon

        ManualPacket manual_pkt('m', temp_reads, 0);
        Session::rx_queue.enqueue(manual_pkt);

        /*
        if (!send_packet(&manual_pkt, servo_pipe)) {     
            std::cout << "Failed to send MP packet" << std::endl;
            //return 1;
        }   
        */


    usleep(1000);
    return;
}




/*
TODO:    (Manual) Processes bitmask of pressed buttons
*/
void ManualControlMode::handleManualButtonCombinations(uint32_t& mask) {
    switch (mask) {

        // (A)
        // Assist/Manual toggle
        case BTN_CROSS:
            std::cout << "Cross button pressed" << std::endl;
            std::cout << "A button pressed" << std::endl;
            // Add more checks as needed in future
            if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::MANUAL) {
                Session::control_mode.store(ControlMode::ASSIST);  // Set control mode to ASSIST
                std::cout << "Control mode set to ASSIST" << std::endl;
            }         

            // Send StatusPacket


            //send_feature('a', 1, 4);

            

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

