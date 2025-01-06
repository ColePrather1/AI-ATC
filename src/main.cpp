

//#include "atc.h"
//#include "ThreadSafeQueue.h"
//#include "QuickThread.h"

#include "atc_threads.h"
//#include "System.h"
#include "atc.h"
#include "Session.h"

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



// Only handles startup and shutdown
int main() {
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
    if (!rf_rx_thread.start()){
        std::cerr << "RF24 RX Thread failed to start" << std::endl;
        return 1;
    }
    if (!rf_tx_thread.start()){
        std::cerr << "RF24 TX Thread failed to start" << std::endl;
        return 1;
    }
    if (!game_controller_thread.start()){
        std::cerr << "Game Controller Thread failed to start" << std::endl;
        return 1;
    }
    if (!sql_thread.start()){
        std::cerr << "SQL Thread failed to start" << std::endl;    
        return 1;
    }

    //if (!comp_thread.start()){
    //    std::cerr << "Computation Thread failed to start" << std::endl;    
    //    return 1;
    //}


    while (!Session::quit_flag.load(std::memory_order_acquire)) {
/*
TODO: Implement Main loop
*/

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

        usleep(10000);
    }

/*
TODO: Implement shutdown procedure failsafe
*/ 
    if (!shutdown()){
        std::cerr << "Shutdown failed" << std::endl;
        return 1;
    }

    return 0;
}





/*

int main() {
    // Register signal handler
    //signal(SIGINT, signalHandler);

    // Create shared queues for inter-thread communication
    //ThreadSafeQueue<Packet> rx_queue;
    //ThreadSafeQueue<Packet> tx_queue;
    //ThreadSafeQueue<LogData> log_queue;
    //ThreadSafeQueue<ControllerData> controller_queue;


    //QuickThread rx_thread(rx_setup, loop);
    //QuickThread tx_thread(tx_queue);
    //QuickThread sql_thread(log_queue);
    //QuickThread comp_thread(controller_queue);


    //QuickThread test_thread(test_setup, test_loop);
    //test_thread.set_queue()



    // Initialize RF24 radio
    RF24 radio(22, 0); // CE and CSN pins
    if (!radio.begin()) {
        std::cerr << "Radio hardware not responding!" << std::endl;
        return 1;
    }

    // Set up radio parameters
    radio.setPALevel(RF24_PA_LOW);
    radio.setChannel(76);
    radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
    radio.startListening();

    // Create thread objects
    RXThread rx_thread(radio, rx_queue);
    TXThread tx_thread(radio, tx_queue);
    SQLLoggerThread sql_thread("project_data.db", log_queue);
    ComputationThread comp_thread(rx_queue, tx_queue, log_queue, controller_queue);
    GameControllerThread gc_thread(controller_queue);

    // Start threads
    std::thread t1(&RXThread::run, &rx_thread);
    std::thread t2(&TXThread::run, &tx_thread);
    std::thread t3(&SQLLoggerThread::run, &sql_thread);
    std::thread t4(&ComputationThread::run, &comp_thread);
    std::thread t5(&GameControllerThread::run, &gc_thread);

    // Main loop
    while (g_running) {


        // Perform any main thread operations here
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Signal threads to stop
    rx_thread.stop();
    tx_thread.stop();
    sql_thread.stop();
    comp_thread.stop();
    gc_thread.stop();

    // Join threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << "All threads have been joined. Exiting." << std::endl;

    return 0;
}


*/




/*

int main() {
    //if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
    //if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0){
    //    std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    //    return 1;
    //}


    //if (!controller_setup()) {}     // If GameController setup fails, don't crash the program
    //if (!radio_setup()) {}      // If RF24 setup fails, don't crash the program


    SDL_Event e;
    bool quit = false;


    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN) {       // delete for production, q input to stop app
            switch (e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    break;
                // Add other key checks here
            }
            }

        }


        receive_data();
        //usleep(100000);



        switch (control_mode){
            case MANUAL:
                //manual_mode();
                manual_send_features();
                manual_btns();

                //manual_send_btns();

                // 1 Check GPS, act for boundary
                // If out of range
                //if (!within_range()) { }

                break;

            case ASSIST:
                assist_send_features();
                assist_send_btns();

                // 1 Check GPS, act for boundary
                //assist_mode();
                break;
            case AUTO:
                //auto_mode();
                break;
            case EMERGENCY:
                //emergency_mode();
                break;
            default:
                break;
        }



    }

    shutdown();
    return 0;
}

*/


