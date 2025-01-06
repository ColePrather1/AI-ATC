#ifndef THREAD_COMPUTE_H
#define THREAD_COMPUTE_H

#pragma once
#include "Common.h"
#include "Session.h"
#include "QuickThread.h"
//#include "rf_rx.h"


static bool compute_setup(){
    // Initialize receiving radio
    RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
    if (!radio_rx.begin()) {
        std::cout << "Failed to initialize receiving radio" << std::endl;
        return false;
    }
    radio_rx.openReadingPipe(1, pipes[5]); // Use pipe 5 for receiving
    radio_rx.setPALevel(RF24_PA_LOW);
    radio_rx.startListening();
    return true;
    //return ATC_RF::rx_setup();
}


/*
TODO: Implement, time to get real
*/
static void compute_loop(){
    if (radio_rx.available()) {
        char received_data[PAYLOAD_SIZE];
        radio_rx.read(&received_data, sizeof(received_data));
        std::cout << "Received from plane: " << received_data << std::endl;
        // Process the received data as needed


        // Parse the received data into a DataPacket struct


        // 1 Check GPS, act for boundary
        // If out of range
        //if (!within_range()) { }

    }
    //usleep(10000);
    
}


extern QuickThread compute_thread(compute_setup, compute_loop);

#endif // THREAD_COMPUTE_H