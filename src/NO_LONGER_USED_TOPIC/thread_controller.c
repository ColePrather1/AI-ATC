#include "threads/thread_controller.hpp"
#include "Session.h"
//#include "QuickThread.h"

//#include "atc_rf.h"
#include "GameController.h"
#include "ControlModes/ControlModes.h"
#include <iostream>


static bool game_controller_setup(){
    //return GameController::controller_setup();

}

//uint32_t getButtonCombinationMask(SDL_GameController* controller);

static void game_controller_loop(){

    Session::ctlr_loop_active.store(true, std::memory_order_release);

    while (Session::ctlr_loop_active.load(std::memory_order_acquire)) {
        if (Session::quit_flag.load(std::memory_order_acquire) && !Session::ctlr_shtdwn.load(std::memory_order_acquire)) {
            Session::ctlr_shtdwn.store(true, std::memory_order_release);
            GameController::controller_shutdown();
            return;
        }


        GameController::handleEvents();

        if (Session::ctlr_paired.load(std::memory_order_acquire)) {
            //GameController::buttonMask = getButtonCombinationMask();
            GameController::getButtonCombinationMask();
        // TODO: Create function pointer for each control mode to replace switch
        // TODO: Create function pointer for each control mode to replace switch
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
        }
        usleep(100);
    }
}


//extern QuickThread game_controller_thread(game_controller_setup, game_controller_loop);

extern QuickThread game_controller_thread(game_controller_setup, game_controller_loop);