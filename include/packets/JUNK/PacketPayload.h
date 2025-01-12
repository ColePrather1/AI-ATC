#ifndef PACKET_PAYLOAD_H
#define PACKET_PAYLOAD_H
#pragma once

#include <bitset>

template < typename T, uint8_t N>
class Payload {
public:
    std::bitset<N> payload;

    Payload() {}
    Payload(std::bitset<22> pld) : payload(pld) {}
    Payload(T pld) {
        payload = createPayload(pld);

    }

    std::bitset<N> createPayload(T pld) {
        std::bitset<N> payload;
        payload = pld;
        return payload;
    }

};

#endif