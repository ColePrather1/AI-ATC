#ifndef RF_RX_H
#define RF_RX_H

#pragma once

#include "Common.h"
#include "Session.h"
#include "rf_com.h"



//extern RF24 radio_rx;

static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio


// Frequenty used memory allocations
Packet incoming_packet*;
uint8_t incoming_packet_size;


bool rx_setup() {
    // Initialize receiving radio
    RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
    if (!radio_rx.begin()) {
        std::cout << "Failed to initialize receiving radio" << std::endl;
        return false;
    }
    radio_rx.openReadingPipe(1, pipes[5]); // Use pipe 5 for receiving
    radio_rx.setChannel(69);
    radio_rx.setPALevel(RF24_PA_LOW);
    radio_rx.setAutoAck(false);
    radio_rx.setDataRate(RF24_250KBPS);
    radio_rx.startListening();
    return true;
}

inline Packet* getPacket() {
    
}


/*
bool process_rx_packet(Packet* packet) {
    switch (packet->type) {
        case PacketType::SYSTEM:
        case PacketType::STATUS:
        case PacketType::PAIRING:
        case PacketType::ACK:
            return 0;

        case PacketType::AUTO:
            return 1;
        
        case PacketType::ASSIST:
        case PacketType::MANUAL:
            return 2;

        case PacketType::ACCEL:
        case PacketType::GYRO:
        case PacketType::MAGNET:
            return 3;

        case PacketType::GPS:
        case PacketType::GPS_ENV:
            return 4;
        
        case PacketType::BAROMETER:
        case PacketType::TEMP_HUMID:
        //case PacketType::SENSOR_PACKET:
            return 5;

        case PacketType::BASE:                      // No Pipe / Error Handling
        default:
            return -1;
    }
}
*/


#endif // RF_RX_H