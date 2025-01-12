#include "threads/thread_packet_process.hpp"

//#include "Common.h"
//#include "../src/Session.h"
//#include "../include/QuickThread.h"

//#include "../src/rf_rx.h"
//#include "PacketProcess.h"

#include "packets/packets.h"

#include "threads/rx_processesing_queue.hpp"

//#include <array>
//#include <span>

static bool packet_process_setup() {
    return true;
}

static void packet_process_loop() {
    if (rx_buffer_queue.empty()) { 
        return; 
    }
    else {
        //reinterpret_cast<Packet*>(rx_buffer_queue.dequeue().buffer.data())->process();
        //BufferItem item = rx_buffer_queue.dequeue();
        //std::byte item = rx_buffer_queue.dequeue();
        reinterpret_cast<Packet*>(rx_buffer_queue.dequeue().data())->process();

        //std::span<std::byte, item.size> buffer_span(item.buffer.data(), item.size);
        //reinterpret_cast<Packet*>(buffer_span.data())->process();
        return;
    }
   return;
}



extern QuickThread packet_process_thread(packet_process_setup, packet_process_loop);
//QuickThread packet_process_thread(packet_process_setup, packet_process_loop);
//inline QuickThread packet_process_thread(packet_process_setup, packet_process_loop);