#ifndef GPS_ENV_H
#define GPS_ENV_H
#pragma once
#include "Common.h"
#include "Session.h"
#include "Packet.h"

// 6 bytes

class GPSEnvPacket : public Packet {
    uint16_t heading;
    uint16_t speed;
    uint8_t sats;
    uint8_t signal_strength;
    //unsigned long timestamp;

    GPSEnvPacket() : Packet(PacketType::GPS_ENV) {}
    GPSEnvPacket(char hdr, uint16_t heading, uint16_t speed, uint8_t sats, uint8_t signal_strenght) : Packet(PacketType::GPS_ENV, hdr) {}


    bool process() override {
        //std::cout << "Processing GPS Env Packet" << std::endl;
        
        // 1) Store Pilot's current GPS Env data
        Session::airplane_current_gps_heading.store(heading);
        Session::airplane_current_gps_speed.store(speed);

        // 2) Send to SQL Logging 
        Logging::insertGPSEnvData(heading, speed, sats, signal_strength);       
        return true;
    }

};

#endif // GPS_ENV_H