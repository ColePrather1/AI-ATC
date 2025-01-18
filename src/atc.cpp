#include "atc.h"


#include "Common.h"
#include "Session.h"
#include "Logging.h"
#include <iostream>

//#include "threads/atc_threads.h"
#include "GameController.h"
//#include "SQL.h"



//bool ATC::within_range(){}

/*
TODO: Implement Plane & GameController Pairing
*/
bool ATC::pair_pilot(){
    //Session::control_mode = ControlMode::ASSIST;
    return 1;
}

/*
TODO: Implement ATC, Plane & GameController Shutdown

TODO: Verify not in flight prior to shutdown

*/
bool ATC::atc_shutdown(){
    if(Session::isFlying.load(std::memory_order_acquire)){
        std::cout << "Cannot shutdown while in flight" << std::endl;
        return 0;
    }
    //SDL_GameControllerClose(controller);
    //SDL_Quit();


    //if (!GameController::controller_shutdown()) {
    //    std::cout << "Game Controller shutdown failed" << std::endl;
    //}
    
    /*
    // If all threads are joinable, join them
    if (rf_rx_thread.joinable() && rf_tx_thread.joinable() && game_controller_thread.joinable() && packet_process_thread.joinable()) {      //  && sql_thread.joinable()
        rf_rx_thread.stop();
        rf_tx_thread.stop();
        packet_process_thread.stop();
        game_controller_thread.stop();
        //sql_thread.stop();
    }

    */

   if (rf_rx_thread.joinable()) { 
       rf_rx_thread.stop();
   }
   std::cout << "rf_rx_thread stopped" << std::endl;

   if (rf_tx_thread.joinable()) { 
       rf_tx_thread.stop();
   }
   std::cout << "rf_tx_thread stopped" << std::endl;

   if (packet_process_thread.joinable()) {
       packet_process_thread.stop();
   }
   std::cout << "packet_process_thread stopped" << std::endl;

   if (game_controller_thread.joinable()) {
        GameController::controller_shutdown();
        game_controller_thread.stop();
   }
   std::cout << "game_controller_thread stopped" << std::endl;


    Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN);
    Logging::stopLogger();
    std::cout << "Logging Thread stopped" << std::endl;

    /*
    if (!Logging::stopLogger()) {
        std::cout << "Logging Thread failed to stop" << std::endl; 
    }
    */

    std::cout << "ATC Shutting down..." << std::endl;
    return 1;

}

/*
bool ATC::setAutoControlMode(){
    //Session::control_mode = ControlMode::AUTO;

    if (Session::control_mode.load(std::memory_order_relaxed) != ControlMode::AUTO) {
        Session::control_mode.store(ControlMode::AUTO, std::memory_order_release);
        return 1;
    }
    return 0;
}

bool ATC::setManualControlMode(){
    //Session::control_mode = ControlMode::MANUAL;

    // Exckudes ControlMode for PARING and RECOVERY

    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::ASSIST) {
        Session::control_mode.store(ControlMode::MANUAL, std::memory_order_release);
        return 1;
    }
    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::TAXI) {
        Session::control_mode.store(ControlMode::MANUAL, std::memory_order_release);
        return 1;
    }

    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::EMERGENCY) {
        // Switch to ASSIST instead for easier ControlMode transition
        Session::control_mode.store(ControlMode::ASSIST, std::memory_order_release);
        return 1;
    }


    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::HOLDING) {
        // Switch to ASSIST instead for easier ControlMode transition
        Session::control_mode.store(ControlMode::ASSIST, std::memory_order_release);
        return 1;
    }
    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::AUTO) {
        Session::control_mode.store(ControlMode::HOLDING, std::memory_order_release);
        return 1;
    }

    if (Session::control_mode.load(std::memory_order_relaxed) == ControlMode::MANUAL) {
        return 0;
    }

    return 0;
}
*/



