#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

#pragma once
#include "Common.h"
#include "Session.h"
#include "QuickThread.h"

#include "atc_rf.h"
#include "GameController.h"
#include "ControlModes.h"


static bool game_controller_setup(){
    return controller_setup();
}

//uint32_t getButtonCombinationMask(SDL_GameController* controller);

static void game_controller_loop(){
    if (Session::ctlr_paired.load(std::memory_order_acquire)) {
        //GameController::buttonMask = getButtonCombinationMask();
        getButtonCombinationMask();
     switch (Session::control_mode.load(std::memory_order_acquire)) {
         case ControlMode::MANUAL:
            ManualControlMode::manualMode();
             break;
         case ControlMode::ASSIST:
            AssistControlMode::assistMode();
             break;
         case ControlMode::AUTO:
            AutoControlMode::autoMode();
             break;
         case ControlMode::EMERGENCY:
            EmergencyControlMode::emergencyMode();
             break;
         case ControlMode::HOLDING:
            HoldingControlMode::holdingMode();
             break;
         case ControlMode::TAXI:
            TaxiControlMode::taxiMode();
             break;
         case ControlMode::PAIRING:
            PairingControlMode::pairingMode();
             break;
         case ControlMode::RECOVERY:
            RecoveryControlMode::recoveryMode();
             break;
         default:
             break;
     }
     usleep(100);
    }
}


extern QuickThread game_controller_thread(game_controller_setup, game_controller_loop);

#endif // THREAD_CONTROLLER_H