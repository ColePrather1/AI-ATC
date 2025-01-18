#include <iostream>
#include <thread>
#include <chrono>

#include "atc.h"


#include "Common.h"
#include "Session.h"
#include "Logging.h"


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


// returns true on success
bool ATC::atc_startup(){

    // Logging
    if (!Logging::startLogger()){    
        std::cout << "Logging Thread failed to start" << std::endl; 
        return false;   
    }
    while(!Session::logger_running.load(std::memory_order_relaxed)){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    Logging::insertEventLog(EventType::SYSTEM_STARTUP);
    std::cout << "Logging Thread started" << std::endl;    


    // GameController
    if (!globalGameController.start()){
        std::cout << "globalGameController failed to start" << std::endl;
        return false;
    }
    std::cout << "globalGameController started." << std::endl;


    /*
    // TODO: add ! after testing finished
    if (!rf_rx_thread.start()){
        std::cout << "RF24 RX Thread failed to start" << std::endl;
        return false;
    }
    std::cout << "RF24 RX Thread started" << std::endl;

    // TODO: add ! after testing finished
    if (rf_tx_thread.start()){
        std::cout << "RF24 TX Thread failed to start" << std::endl;
        return false;
    }
    std::cout << "RF24 TX Thread started" << std::endl;
    */

    return true;
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
    Session::atc_shtdwn.store(true, std::memory_order_release);
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

   Session::rf_rx_shtdwn.store(true, std::memory_order_release);
   if (rf_rx_thread.joinable()) { 
       rf_rx_thread.stop();
   }
   std::cout << "rf_rx_thread stopped" << std::endl;
   Session::rf_rx_shtdwn.store(false, std::memory_order_release);
   Session::rf_rx_finished.store(true, std::memory_order_release);


   Session::rf_tx_shtdwn.store(true, std::memory_order_release);
   if (rf_tx_thread.joinable()) { 
       rf_tx_thread.stop();
   }
   std::cout << "rf_tx_thread stopped" << std::endl;
   Session::rf_tx_shtdwn.store(false, std::memory_order_release);
   Session::rf_tx_finished.store(true, std::memory_order_release);


   Session::computer_shtdwn.store(true, std::memory_order_release);
   if (packet_process_thread.joinable()) {
       packet_process_thread.stop();
   }
   std::cout << "packet_process_thread stopped" << std::endl;
   Session::computer_shtdwn.store(false, std::memory_order_release);
   Session::computer_finished.store(true, std::memory_order_release);


   Session::ctlr_shtdwn.store(true, std::memory_order_release);
   if (!globalGameController.stop()) {
        std::cout << "Game Controller shutdown failed" << std::endl;
        //GameController::controller_shutdown();
        //game_controller_thread.stop();
   }
   std::cout << "globalGameController stopped" << std::endl;
   Session::ctlr_shtdwn.store(false, std::memory_order_release);
   Session::ctlr_finished.store(true, std::memory_order_release);


   //if (game_controller_thread.joinable()) {
   //     GameController::controller_shutdown();
   //     game_controller_thread.stop();
   //}
   //std::cout << "game_controller_thread stopped" << std::endl;

    Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN);
    Session::logger_shtdwn.store(true, std::memory_order_release);
    Logging::stopLogger();
    std::cout << "Logging Thread stopped" << std::endl;
    Session::logger_shtdwn.store(false, std::memory_order_release);
    Session::logger_finished.store(true, std::memory_order_release);

    /*
    if (!Logging::stopLogger()) {
        std::cout << "Logging Thread failed to stop" << std::endl; 
    }
    */

    Session::atc_shtdwn.store(false, std::memory_order_release);
    Session::atc_finished.store(true, std::memory_order_release);
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



