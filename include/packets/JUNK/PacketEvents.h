#ifndef PACKET_EVENTS_H
#define PACKET_EVENTS_H
#pragma once

#include "Common.h"
#include "Session.h"
#include "packets.h"


void accel_process();
void ack_process();
void assist_process();
void auto_process();
void barometer_process();
//void frag_process();
void gps_env_process();
void gps_process();
void gyro_process();
//void log_process();
void magnet_process();
void manual_process();
void pair_process();
void pid_process();
void status_process();
void system_process();
void temp_humid_process();



void system_process(){
    std::cout << "System Packet Received from planes" << std::endl;

    Bitmask bm(incoming_packet.data);

    if (ATC_synced != Airplane_synced) {
        //ATC_synced = Airplane_synced;
        //encode_flight_parameters();
    }

}





#endif // PACKET_EVENTS_H