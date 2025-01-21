
#include <iostream>
//#include <cctype>
#include <thread>
#include "atc.h"
#include "Session.h"
#include "Logging.h"
#include "GameController.h"



/*
bool keyboard_quit(){
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit_flag.store(true, std::memory_order_release);
            } 
            else if (e.type == SDL_KEYDOWN) {       // delete for production, q input to stop app
            switch (e.key.keysym.sym) {
                case SDLK_q:
                    quit_flag.store(true, std::memory_order_release);
                    break;
                // Add other key checks here
            }
            }

        }

}
*/

// Shutdown Process
//static bool quit_called = false;

std::atomic<bool> quit_called{false};
std::atomic<bool> shutdown_status{false};

int quit(){
    //if (quit_called){
    //    return 1;
    //}
    //quit_called = true;
    quit_called.store(true, std::memory_order_acquire);
    Session::quit_flag.store(true, std::memory_order_relaxed);

    bool success = ATC::atc_shutdown();
    if (!success){
        std::cout << "quit(): Shutdown failed" << std::endl;
        //shutdown_status.store(true, std::memory_order_release);
        return 1;
    }

    //while (Session::atc_shtdwn.load(std::memory_order_relaxed)){
    //    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //}

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (!Session::atc_finished.load(std::memory_order_relaxed)){
        std::cout << "quit(): Shutdown failed, ATC not finished." << std::endl;
        //Session::program_finished.store(true, std::memory_order_release);
        //shutdown_status.store(true, std::memory_order_release);
        return 1;
    }
    std::cout << "quit(): Shutdown successful" << std::endl;
    //Session::program_finished.store(true, std::memory_order_release);
    //shutdown_status.store(false, std::memory_order_release);
    return 0;
}


#include <atomic>
#include <chrono>
#include <cstdint>
#include <termios.h>
#include <unistd.h>

class MainThread {
public:
    uint8_t data;
    std::thread keyboard_thread;
    std::atomic<bool> quit_flag{false};

    MainThread(uint8_t input) : data(input) {
        keyboard_thread = std::thread(&MainThread::keyboardInputThread, this);
    }

    ~MainThread() {
        quit_flag.store(true, std::memory_order_release);
        if (keyboard_thread.joinable()) {
            keyboard_thread.join();
        }
    }

    void keyboardInputThread() {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        while (!quit_flag.load(std::memory_order_relaxed)) {
            fd_set rfds;
            struct timeval tv;
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 10000;

            int retval = select(1, &rfds, NULL, NULL, &tv);
            if (retval == -1) {
                perror("select()");
            } else if (retval) {
                char ch = getchar();
                if (ch == 'q' || ch == 'Q') {
                    std::cout << "Keyboard quit triggered ..." << std::endl;
                    if (!quit_called.load(std::memory_order_acquire)) {
                        quit();
                    }
                    break;
                    /*
                    Session::quit_flag.store(true, std::memory_order_release);
                    if (!Session::atc_shtdwn.load(std::memory_order_relaxed)) {
                        if (!ATC::atc_shutdown()) {
                            std::cout << "(Keyboard) ATC shutdown failed" << std::endl;
                        }
                        break;                
                    }
                    */
                }
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};







// Only handles startup and shutdown
int main() {

    // Startup Process
    MainThread main_thread(static_cast<uint8_t>(0));
    if (!ATC::atc_startup()){
        std::cout << "ATC startup failed" << std::endl;
        //Session::quit_flag.store(true, std::memory_order_relaxed);
        //ATC::atc_shutdown();
        //return quit();
        //bool success = quit();
        //if (!success){
        //    //std::cout << "Shutdown failed" << std::endl;
        //    return 1;
        //}
        //quit();

        if (!quit_called.load(std::memory_order_acquire)) {
            quit();
        }
        return 1;       // Don't need to check quit() return value because program failed regardless
    }
    std::cout << "ATC startup successful" << std::endl;

    // Main Process
    std::cout << "Main process starting..." << std::endl;
    while (!Session::quit_flag.load(std::memory_order_relaxed)) {
        // TODO: Implement Main loop
        //std::cout << "Main Loop" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        continue;
    }

    std::cout << "Main process ending..." << std::endl;

    //if (!quit_called.load(std::memory_order_acquire)){
    //    bool return_val = quit();
    //}

    //bool success = quit();
    //if (!success){
    //    std::cout << "Shutdown failed" << std::endl;
    //    return 1;
    //}

    return 0;
    //return success;
}



    //if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
    //if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0){
    //    std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    //    return 1;
    //}


    //if (!controller_setup()) {}     // If GameController setup fails, don't crash the program
    //if (!radio_setup()) {}      // If RF24 setup fails, don't crash the program



/*
    Program Initialization
*/





    /*
    // TODO: add ! after testing finished
    if (!rf_rx_thread.start()){
        std::cout << "RF24 RX Thread failed to start" << std::endl;
        return 1;
    }
    std::cout << "RF24 RX Thread started" << std::endl;

    // TODO: add ! after testing finished
    if (rf_tx_thread.start()){
        std::cout << "RF24 TX Thread failed to start" << std::endl;
        return 1;
    }
    std::cout << "RF24 TX Thread started" << std::endl;
    */

    //enable_ble();
    //usleep(100000);

    //if (!game_controller_thread.start()){
    //    std::cout << "Game Controller Thread failed to start" << std::endl;
    //    return 1;
    //}
    //std::cout << "Game Controller Thread started" << std::endl;

    //if (!globalGameController.start()){
    //    std::cout << "globalGameController failed to start" << std::endl;
    //    return 1;
    //}
    //std::cout << "globalGameController started." << std::endl;


    /*
    if (!sql_thread.start()){
        std::cerr << "SQL Thread failed to start" << std::endl;    
        return 1;
    }
    */

    //if (!comp_thread.start()){
    //    std::cerr << "Computation Thread failed to start" << std::endl;    
    //    return 1;
    //}



    //std::cout << "Main process starting..." << std::endl;
    //char input;
    //while (true){
    //    if (std::cin.get(input)){
    //        if (std::tolower(input) == 'q') {
    //            std::cout << "Exiting..." << std::endl;
    //            Session::quit_flag.store(true, std::memory_order_release);
    //            //return 0;
    //            break;
    //        }
    //    }
    //}
    //Session::quit_flag.store(true, std::memory_order_release);

    // TODO: Use after finished dev testing
    //while (!Session::quit_flag.load(std::memory_order_acquire)) {
    //    // TODO: Implement Main loop
    //    std::cout << "Main Loop" << std::endl;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    //}


    // TODO: Implement shutdown procedure failsafe
    //if (!ATC::atc_shutdown()){
    //if (Session::atc){
    //    std::cout << "Shutdown failed" << std::endl;
    //    return 1;
    //}

//    if (!Session::atc_finished.load(std::memory_order_relaxed)){
//        std::cout << "Shutdown failed" << std::endl;
//        return 1;
//    }
//    std::cout << "Shutdown successful" << std::endl;
//    return 0;
//}


