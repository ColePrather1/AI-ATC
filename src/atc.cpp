#include <iostream>
#include <thread>
#include <chrono>
#include "atc.h"
#include "Common.h"
#include "Session.h"
#include "Logging.h"
#include "GameController.h"
#include "threads/atc_threads.h"

// TODO: Implement Plane & GameController Pairing
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
    // Wait for logging to start, then set active
    while(Session::logger_started.load(std::memory_order_relaxed)
        && !Session::logger_loop_active.load(std::memory_order_relaxed)
        && !Session::quit_flag.load(std::memory_order_relaxed)){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    Session::logger_active.store(true, std::memory_order_release);
    Logging::insertEventLog(EventType::SYSTEM_STARTUP);
    std::cout << "Logging Thread started" << std::endl;    

    // ATC active , since logger is active
    Session::atc_active.store(true, std::memory_order_release);



    // GameController
    if (!globalGameController.start()){
        std::cout << "globalGameController failed to start" << std::endl;
        return false;
    }
    Session::ctlr_active.store(true, std::memory_order_release);
    std::cout << "globalGameController started." << std::endl;


    // Process
    if (!packet_process_thread.start()){
        std::cout << "Process Thread failed to start" << std::endl;
        return false;
    }
    Session::process_active.store(true, std::memory_order_release);
    std::cout << "Process Thread started" << std::endl;

    
    // RF Receiver
    if (!rf_rx_thread.start()){
        std::cout << "RF24 RX Thread failed to start" << std::endl;
        return false;
    }
    Session::rf_rx_active.store(true, std::memory_order_release);
    std::cout << "RF24 RX Thread started" << std::endl;


    // RF Transmitter
    if (!rf_tx_thread.start()){
        std::cout << "RF24 TX Thread failed to start" << std::endl;
        return false;
    }
    Session::rf_tx_active.store(true, std::memory_order_release);
    std::cout << "RF24 TX Thread started" << std::endl;
    

    Logging::insertEventLog(EventType::SYSTEM_STARTUP);
    Logging::insertEventLog(EventType::RF_RX_START);
    Logging::insertEventLog(EventType::RF_TX_START);
    Logging::insertEventLog(EventType::PROCESS_START);

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

    if (Session::rf_rx_active.load(std::memory_order_relaxed)) {
        std::cout << "rf_rx_thread stopping..." << std::endl;
        Session::rf_rx_shtdwn.store(true, std::memory_order_release);
        Session::rf_rx_loop_active.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (rf_rx_thread.joinable()) { 
            rf_rx_thread.stop();
        }
        std::cout << "rf_rx_thread stopped" << std::endl << std::endl;
        Session::rf_rx_active.store(false, std::memory_order_release);
        Session::rf_rx_shtdwn.store(false, std::memory_order_release);
        Session::rf_rx_finished.store(true, std::memory_order_release);    
    }
    else{
        std::cout << "rf_rx_thread not active" << std::endl << std::endl;
    }



    if (Session::rf_tx_active.load(std::memory_order_relaxed)) {
        std::cout << "rf_tx_thread stopping..." << std::endl;
        Session::rf_tx_shtdwn.store(true, std::memory_order_release);
        Session::rf_tx_loop_active.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (rf_tx_thread.joinable()) { 
            rf_tx_thread.stop();
        }
        std::cout << "rf_tx_thread stopped" << std::endl << std::endl;
        Session::rf_tx_active.store(false, std::memory_order_release);
        Session::rf_tx_shtdwn.store(false, std::memory_order_release);
        Session::rf_tx_finished.store(true, std::memory_order_release);
    }
    else{
        std::cout << "rf_tx_thread not active" << std::endl << std::endl;
    }

    if (Session::process_active.load(std::memory_order_relaxed)) {
        std::cout << "packet_process_thread stopping..." << std::endl;
        Session::process_shtdwn.store(true, std::memory_order_release);
        Session::process_loop_active.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (packet_process_thread.joinable()) {
            packet_process_thread.stop();
        }
        std::cout << "packet_process_thread stopped" << std::endl << std::endl;
        Session::process_active.store(false, std::memory_order_release);
        Session::process_shtdwn.store(false, std::memory_order_release);
        Session::process_finished.store(true, std::memory_order_release);
    }
    else{
        std::cout << "packet_process_thread not active" << std::endl << std::endl;
    }


    if (Session::ctlr_active.load(std::memory_order_relaxed)) {
        std::cout << "globalGameController stopping..." << std::endl;
        //Session::ctlr_shtdwn.store(true, std::memory_order_release);
        //Session::ctlr_loop_active.store(false, std::memory_order_release);  // happens in gGC.stop()
        if (!globalGameController.stop()) {
             std::cout << "Game Controller shutdown failed" << std::endl;
        }
        std::cout << "globalGameController stopped" << std::endl << std::endl;
        Session::ctlr_active.store(false, std::memory_order_release);
        //Session::ctlr_shtdwn.store(false, std::memory_order_release);
        Session::ctlr_finished.store(true, std::memory_order_release);
    }
    else{
        std::cout << "globalGameController not active" << std::endl << std::endl;
    }

    Logging::insertEventLog(EventType::RF_RX_STOP);
    Logging::insertEventLog(EventType::RF_TX_STOP);
    Logging::insertEventLog(EventType::PROCESS_STOP);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));   // Allow time for final statements

    if (Session::logger_active.load(std::memory_order_relaxed)) {
        std::cout << "Logging Thread stopping..." << std::endl;
        Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN);
        Session::logger_shtdwn.store(true, std::memory_order_release);
        Logging::stopLogger();
        std::cout << "Logging Thread stopped" << std::endl << std::endl;
        Session::logger_active.store(false, std::memory_order_release);
        Session::logger_shtdwn.store(false, std::memory_order_release);
    }
    else{
        std::cout << "Logging Thread not active" << std::endl << std::endl;
    }

    Session::atc_active.store(false, std::memory_order_release);
    Session::atc_finished.store(true, std::memory_order_release);
    Session::atc_shtdwn.store(false, std::memory_order_release);
    std::cout << "ATC Shutting down..." << std::endl << std::endl;
    return 1;

}
