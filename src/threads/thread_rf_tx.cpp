#include "threads/thread_rf_tx.hpp"

#include "Session.h"
#include "Logging.h"
#include "QuickThread.h"
#include "rf_com.h"
#include "RadioTxQueue.h"

#include "packets/packets.h"
#include "EventTypes.h"
#include <iostream>
#include <vector>

bool send_packet(Packet* packet, const int send_pipe);

static RF24 radio_tx(22, 0); // CE, CSN pins for transmitting radio

static bool rf_tx_setup(){
    // Initialize transmitting radio
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (!radio_tx.begin()) {
        Logging::insertEventLog(EventType::RF_TX_FAILED_TO_START);
        std::cout << "Failed to initialize transmitting radio" << std::endl;
        return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    radio_tx.setPALevel(RF24_PA_LOW);
    //radio_tx.setAutoAck(false);
    radio_tx.setDataRate(RF24_250KBPS);
    //radio_tx.setChannel(76);

    radio_tx.stopListening();
    radio_tx.openWritingPipe(pipes[0]);     // Initial pipe for comm with Pilot
    radio_tx.openWritingPipe(pipes[1]);
    radio_tx.openWritingPipe(pipes[2]);
    //radio_tx.openWritingPipe(pipes[3]);
    
    return true;
}

static void rf_tx_loop(){
    Session::rf_tx_loop_active.store(true, std::memory_order_release);
    std::atomic<int> rf_tx_active_pipe {0};
    while (Session::rf_tx_loop_active.load(std::memory_order_relaxed) && !Session::quit_flag.load(std::memory_order_relaxed)) {
        Packet* packet;
        if (!RadioTx::tx_queue.empty()) {          // If Packet ready to send
            int pipe = getPipe(RadioTx::tx_queue.front());
            if (pipe >= 0) {
                send_packet(RadioTx::tx_queue.dequeue(), pipe);
            }
            else {
                std::cout << "Invalid pipe, dropping packet" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        continue;
    }
    Session::rf_tx_loop_active.store(false, std::memory_order_release);
    return;
}

bool send_packet(Packet* packet, int send_pipe) {
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

    bool result = radio_tx.write(packet->payload.data(), sizeof(packet->payload.data()));

    if (!result) {
        std::cout << "Failed to send packet" << std::endl;
        return false;
    }
    std::cout << "Packet sent" << std::endl;
    return true;
}

extern QuickThread rf_tx_thread(rf_tx_setup, rf_tx_loop);