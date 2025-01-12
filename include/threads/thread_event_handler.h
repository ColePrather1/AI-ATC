#ifndef THREAD_EVENT_HANDLER_H
#define THREAD_EVENT_HANDLER_H
#pragma once


#include "Common.h"
#include "Session.h"
#include "QuickThread.h"

#include "../src/EventActions.h"

EventActions Event_Handler;

static bool event_handler_setup() {


    return true;
}

static void event_handler_loop() {

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



extern QuickThread event_handler_thread(event_handler_setup, event_handler_loop);



#endif // THREAD_EVENT_HANDLER_H