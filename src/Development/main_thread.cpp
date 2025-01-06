#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <csignal>
//#include "RXThread.h"
//#include "TXThread.h"
//#include "SQLLoggerThread.h"
//#include "ComputationThread.h"
//#include "GameControllerThread.h"

#include "atc.h"


//#include "ThreadSafeQueue.h"
//#include "QuickThread.h"


// Compile
//g++ -std=c++11 -pthread -fopenmp `sdl2-config --cflags --libs` `pkg-config --cflags --libs sqlite3` -lrf24 -o my_project main.cpp




// Signal handler for graceful shutdown
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    g_running = false;
}
    // Register signal handler
    //signal(SIGINT, signalHandler);



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


