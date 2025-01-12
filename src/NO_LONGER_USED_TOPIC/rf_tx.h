#ifndef RF_TX_H
#define RF_TX_H

#pragma once

#include "Common.h"
#include "Session.h"
#include "rf_com.h"

#include "ThreadSafeQueue.h"

//extern RF24 radio_tx;


namespace RadioTx {
    ThreadSafeQueue<Packet> tx_queue;
    //RF24 radio_tx;
}




//bool send_packet(Packet* packet, const uint8_t send_pipe)

bool send_packet(Packet* packet, const int send_pipe) {
    if (send_pipe >= 6) {
        std::cout << "Invalid pipe number" << std::endl;
        return false;
    }
    if (send_pipe != rf_tx_active_pipe.load(std::memory_order_acquire)) {
        rf_tx_active_pipe.store(send_pipe, std::memory_order_release);
        radio_tx.setWritingPipe(pipes[send_pipe]);     // pipes[Session::rf_tx_active_pipe]
        usleep(10000);
    }

    if (!radio_tx.write(packet, sizeof(packet))) {
        std::cout << "Failed to send packet" << std::endl;
        return false;
    }
    return true;
}





#endif // RF_TX_H