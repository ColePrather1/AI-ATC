#include "include/packets/packets.h"
#include <chrono>
#include <array>
#include <cstdint>
#include <iostream>

#include <Bitmask.h>

#include <random>







/*
Test 0
    Tx:
        ManualPacket -> Binary -> uint64_t
*/
bool test0() {


    // Create ManualPacket data
    std::array<uint16_t, 5> feat_vals;
    feat_vals[0] = 123;
    feat_vals[1] = 456;
    feat_vals[2] = 789;
    feat_vals[3] = 101112;
    feat_vals[4] = 131415;
    std::chrono::system_clock::time_point time = std::chrono::system_clock::now();

    // Create ManualPacket
    ManualPacket manual_packet = ManualPacket('m', feat_vals, time);
    int size = sizeof(manual_packet);

    // Create buffer 
    std::array<uint8_t, size> buffer;

    Packet* packet;
    std::memcpy(&packet, buffer.data(), sizeof(Packet));


    std::cout << "Packet size: " << size << std::endl;
    std::cout << "Packet type: " << (int)packet->type << std::endl;
    std::cout << "Packet header: " << packet->header << std::endl;
    std::cout << "Packet timestamp: " << packet->timestamp << std::endl;


    return true;
}

/*
Test 1
    Rx:
        uint64_t -> Binary -> ManualPacket
*/
bool test1() {

    int payloadSize = 24;

    // Create buffer 
    std::array<uint8_t, size> buffer;

    // Fill buffer
    for (int i = 0; i < payloadSize; i++) {
        buffer[i] = std::rand() % 256;
    }

    Packet* packet;
    std::memcpy(&packet, buffer.data(), sizeof(Packet));

    return true;
}


/*
Test 2
    Packet* ptr = uint64_t
    type = ptr->type
*/
bool test2() {

    return true;
}




//Bitmask test = Bitmask(3480);

int main() {

    test0();

    return 0;
}

