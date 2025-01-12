#ifndef THREAD_RF_TX_H
#define THREAD_RF_TX_H
#pragma once
//#include "Common.h"
//#include "Session.h"
#include "QuickThread.h"
//#include "atc_rf.h"

//#include "rf_tx.h"


//RF24 radio_tx(22, 0); // CE, CSN pins for transmitting radio
/*
static bool rf_tx_setup(){
    // Initialize transmitting radio
    //RF24 radio_tx(22, 0); // CE, CSN pins for transmitting radio
    if (!radio_tx.begin()) {
        std::cout << "Failed to initialize transmitting radio" << std::endl;
        return false;
    }
    radio_tx.stopListening();
    radio_tx.openWritingPipe(pipes[0]);     // Initial pipe for comm with Pilot
    radio_tx.setChannel(69);
    //radio_tx.openWritingPipe(pipes[1]);
    //radio_tx.openWritingPipe(pipes[2]);
    //radio_tx.openWritingPipe(pipes[3]);
    
    radio_tx.setPALevel(RF24_PA_LOW);
    radio_tx.setAutoAck(false);
    radio_tx.setDataRate(RF24_250KBPS);
    return true;

    //return ATC_RF::tx_setup();
}

// array of all packets to prevent repeat allocation
//Packet tx_packets[NUM_FEATS];
// Queue of pointers to packets to be transmitted

static void rf_tx_loop(){
    Packet& packet;
    if (!tx_queue.isEmpty()) {          // If Packet ready to send
        tx_queue.dequeue(packet);
        if (getPipe(packet) >=0  ) {
            send_packet(&packet, getPipe(packet));
            usleep(1000);
        }
        else {
            std::cout << "Invalid pipe, dropping packet" << std::endl;
        } // Error with packet
    }
    else {
        usleep(100);
    }
    
    

}
*/

//extern QuickThread rf_tx_thread(rf_tx_setup, rf_tx_loop);
extern QuickThread rf_tx_thread;

#endif // THREAD_RF_TX_H