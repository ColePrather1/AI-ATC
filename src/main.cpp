#include <iostream>
#include <thread>
#include "atc.h"
#include "Session.h"
#include "SessionControl.h"
#include "RadioTx.h"
#include "Logging.h"
#include "GameController.h"
#include "main.h"



int quit(){
    quit_called.store(true, std::memory_order_acquire);
    Session::quit_flag.store(true, std::memory_order_relaxed);

    bool success = ATC::atc_shutdown();
    if (!success){
        std::cout << "quit(): Shutdown failed" << std::endl;
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (!Session::atc_finished.load(std::memory_order_relaxed)){
        std::cout << "quit(): Shutdown failed, ATC not finished." << std::endl;
        return 1;
    }
    std::cout << "quit(): Shutdown successful" << std::endl;
    Session::program_finished.store(true, std::memory_order_release);
    return 0;
}





// Currently only handles startup and shutdown
int main() {

    // Startup Process
    MainThread main_thread(static_cast<uint8_t>(0));

    if (!main_thread.start()){
        std::cout << "Main thread startup failed" << std::endl;
        return 1;
    }
    std::cout << "Main thread startup successful" << std::endl;

    if (!ATC::atc_startup()){
        std::cout << "ATC startup failed" << std::endl;
        if (!quit_called.load(std::memory_order_acquire)) {
            quit();
        }
        return 1;
    }
    std::cout << "ATC startup successful" << std::endl;


    // Wait for Plane connection
    while (!Session::plane_connected.load(std::memory_order_relaxed)) {
        //std::cout << "Waiting for plane connection..." << std::endl;
        Packet* packet = new EventPacket('e', EventType::PAIR_ATC_REQUEST);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        continue;
    }
    std::cout << "Plane connection successful" << std::endl;


    // Main Process
    std::cout << "Main process starting..." << std::endl;
    while (!Session::quit_flag.load(std::memory_order_relaxed)) {
        // TODO: Implement Main loop
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        continue;
    }

    std::cout << "Main process ending..." << std::endl;

    while (!Session::program_finished.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        continue;
    }
    std::cout << "\nProgram closed successfully." << std::endl;

    return 0;
}