#include "threads/thread_rf_tx.hpp"

#include "Session.h"
#include "QuickThread.h"
#include "rf_com.h"
#include "RadioTxQueue.h"

#include "packets/packets.h"
#include <iostream>
//#include "atc_rf.h"

//#include "rf_tx.h"

bool send_packet(Packet* packet, const int send_pipe);

static RF24 radio_tx(22, 0); // CE, CSN pins for transmitting radio

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
    while (true) {
        std::cout << "RF24 TX Thread running in da loop" << std::endl;
        Packet* packet;
        if (!RadioTx::tx_queue.empty()) {          // If Packet ready to send
            //RadioTx::tx_queue.dequeue(packet);
            int pipe = getPipe(RadioTx::tx_queue.front());
            if (pipe >= 0) {
                send_packet(RadioTx::tx_queue.dequeue(), pipe);
                //send_packet(RadioTx::tx_queue.front(), pipe);
                //RadioTx::tx_queue.dequeue();
                //usleep(1000);
            }
            else {
                std::cout << "Invalid pipe, dropping packet" << std::endl;
            }
            /*
            if (getPipe(packet) >=0  ) {
                //send_packet(packet, //getPipe(RadioTx::tx_queue.front()));
                send_packet(packet, getPipe(packet));
                usleep(1000);
            }
            else {
                std::cout << "Invalid pipe, dropping packet" << std::endl;
            } // Error with packet
            */
        }
        else {
            //usleep(100);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    
    }
}

bool send_packet(Packet* packet, const int send_pipe) {
    if (send_pipe >= 6) {
        std::cout << "Invalid pipe number" << std::endl;
        return false;
    }
    if (send_pipe != rf_tx_active_pipe.load(std::memory_order_acquire)) {
        rf_tx_active_pipe.store(send_pipe, std::memory_order_release);
        //radio_tx.setWritingPipe(pipes[send_pipe]);     // pipes[Session::rf_tx_active_pipe]  // TODO: Implement setWritingPipe
        radio_tx.openWritingPipe(pipes[send_pipe]);     // pipes[Session::rf_tx_active_pipe]
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if (!radio_tx.write(packet, sizeof(packet))) {
        std::cout << "Failed to send packet" << std::endl;
        return false;
    }
    return true;
}

extern QuickThread rf_tx_thread(rf_tx_setup, rf_tx_loop);