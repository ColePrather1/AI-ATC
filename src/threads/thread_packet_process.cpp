#include "threads/thread_packet_process.hpp"

//#include "Common.h"
//#include "../src/Session.h"
//#include "../include/QuickThread.h"

//#include "../src/rf_rx.h"
//#include "PacketProcess.h"

#include "packets/packets.h"

#include "threads/rx_processesing_queue.hpp"
#include "Session.h"
#include <thread>

//#include <array>
//#include <span>

static bool packet_process_setup() {
    return true;
}

static void packet_process_loop() {
    Session::process_loop_active.store(true, std::memory_order_release);
    while (Session::process_loop_active.load(std::memory_order_relaxed) && !Session::quit_flag.load(std::memory_order_relaxed)) {
        
    
        if (rx_buffer_queue.empty()) { 
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue; 
        }
        else {
            //reinterpret_cast<Packet*>(rx_buffer_queue.dequeue().buffer.data())->process();
            reinterpret_cast<Packet*>(rx_buffer_queue.dequeue()->data())->process();
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        continue;
    }
    Session::process_loop_active.store(false, std::memory_order_release);
    return;
}



extern QuickThread packet_process_thread(packet_process_setup, packet_process_loop);
