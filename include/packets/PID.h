#ifndef PID_H
#define PID_H
#pragma once
#include "Packet.h"
#include "PIDFeature.h"


class PIDPacket : public Packet {
public:
    PIDFeature feature_id;
    double Kp, Ki, Kd;

    PIDPacket(char hdr, PIDFeature feature_id, double Kp, double Ki, double Kd);
    void process() override;


    /*

    uint32_t data_size;
    uint8_t data[];  // Flexible array member

    static EventDataPacket* create(EventType type, const void* data, uint32_t size) {
        void* memory = ::operator new(sizeof(PIDPacket) + size);
        PIDPacket* packet = new(memory) PIDPacket();
        packet->event_type = type;
        packet->data_size = size;
        std::memcpy(packet->data, data, size);
        return packet;
    }

    static void destroy(EventDataPacket* packet) {
        packet->~EventDataPacket();
        ::operator delete(packet);
    }
    */


};

#endif // PID_H