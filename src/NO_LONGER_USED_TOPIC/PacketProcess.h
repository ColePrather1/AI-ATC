#ifndef PACKET_PROCESS_H
#define PACKET_PROCESS_H
#pragma once


#include "PacketEvents.h"

//bool process_rx_packet(Packet* packet) {
bool process_rx_packet(Packet& packet) {
    switch (packet->type) {
        case PacketType::SYSTEM:
            system_process();
            break;
        case PacketType::STATUS:
            status_process();
            break;
        case PacketType::PAIRING:
            pairing_process();
            break;
        case PacketType::ACK:
            ack_process();
            break;

        /*
        case PacketType::AUTO:
            auto_process();
            break;
        case PacketType::ASSIST:
            assist_process();
            break;
        case PacketType::MANUAL:
            manual_process();
            break;
        */
            
        case PacketType::ACCEL:
            accel_process();
            break;
        case PacketType::GYRO:
            gyro_process();
            break;
        case PacketType::MAGNET:
            magnet_process();
            break;

        case PacketType::GPS:
            gps_process();
            break;
        case PacketType::GPS_ENV:
            gps_env_process();
            break;
        
        case PacketType::BAROMETER:
            barometer_process();
            break;
        case PacketType::TEMP_HUMID:
            temp_humid_process();
            break;

        case PacketType::BASE:                      // No Pipe / Error Handling
        default:
            return -1;
    }
}





#endif // PACKET_PROCESS_H