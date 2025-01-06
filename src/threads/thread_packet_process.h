#ifndef THREAD_PACKET_PROCESS_H
#define THREAD_PACKET_PROCESS_H
#pragma once


#include "Common.h"
#include "Session.h"
#include "QuickThread.h"

#include "rf_rx.h"
#include "PacketProcess.h"

//#include <future>

//#include <array>

//static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
//static std::array<uint8_t, PAYLOAD_SIZE> rx_buffer;

static bool packet_process_setup() {

    return true;
}

static void packet_process_loop() {

    // If empty, do nothing
    if (Session::rx_processing_queue.empty()) { 
        return; 
    }
    else {
        //Packet* new_packet; Session::rx_processing_queue.front();
        Packet* new_packet = Session::rx_processing_queue.dequeue();  
        new_packet->process();
        delete new_packet;
        return;

/*
TODO: Implement async processing (Futures, clean up in main loop)
        std::future<void> future = std::async(std::launch::async, new_packet->process()); delete new_packet;
*/

    }
   return;
}



extern QuickThread packet_process_thread(packet_process_setup, packet_process_loop);

#endif // THREAD_PACKET_PROCESS_H

