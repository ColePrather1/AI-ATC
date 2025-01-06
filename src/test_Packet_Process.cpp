#ifndef THREAD_RF_RX_H
#define THREAD_RF_RX_H

#pragma once
#include "Common.h"
#include "Session.h"
#include "QuickThread.h"
#include "rf_rx.h"
#include <array>

static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
static std::array<uint8_t, PAYLOAD_SIZE> rx_buffer;

static bool rf_rx_setup() {
    if (!radio_rx.begin()) {
        std::cerr << "Failed to initialize receiving radio" << std::endl;
        return false;
    }
    radio_rx.openReadingPipe(1, pipes[5]); // Use pipe 5 for receiving
    radio_rx.setPALevel(RF24_PA_LOW);
    radio_rx.startListening();
    return true;
}

static void rf_rx_loop() {
    uint8_t pipe;
    if (radio_rx.available(&pipe)) {
        uint8_t bytes = radio_rx.getPayloadSize();
        radio_rx.read(rx_buffer.data(), bytes);
        
        Packet incoming_packet;
        if (decode_packet(rx_buffer.data(), bytes, incoming_packet)) {
            Session::rx_queue.enqueue(std::move(incoming_packet));
        } else {
            std::cerr << "Failed to decode packet" << std::endl;
        }
    }
}

bool decode_packet(const uint8_t* data, uint8_t size, Packet& packet) {
    // Implement packet decoding logic here
    // Return true if successful, false otherwise
    return true;
}

extern QuickThread rf_rx_thread(rf_rx_setup, rf_rx_loop);

#endif // THREAD_RF_RX_H
