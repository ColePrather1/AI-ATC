#ifndef ATC_H
#define ATC_H

#pragma once
//#include "common.h"
//#include "Session.h"

//#include "GameController.h"
//#include "atc_rf.h"
//#include "SQL.h"

//#include <vector>
//#include <iostream>
//#include <cstring>
//#include <unistd.h>



//using namespace std;

namespace ATC {
    // Returns 1 if PILOT is within ATC_RADIUS_METERS (uses GPS coordinates)
    bool within_range();
    bool pair_pilot();
    bool atc_shutdown();


    // Control Modes
    bool setAutoControlMode();
    bool setManualControlMode();
    bool setAssistControlMode();
    bool setEmergencyControlMode();
    bool setHoldingPatternControlMode();
    bool setTaxiOnlyControlMode();

    // Flight Status

}




//void assist_send_features();
//void manual_send_features();
//void manual_btns_simple();
//void manual_btns();
//void control_ps5_controller(SDL_GameController* controller, Uint8 red, Uint8 green, Uint8 blue, Uint8 left_trigger, Uint8 right_trigger);
//void assist_send_btns();



#endif // ATC_H