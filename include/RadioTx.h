#ifndef RADIOTX_H
#define RADIOTX_H
#pragma once
#include "packets/packets.h"
#include "RadioTxQueue.h"

/*
    Transmit to plane
*/
inline void sendToPlane(Packet* packet){
    RadioTx::tx_queue.enqueue(packet);
    return;
}

#endif // RADIOTX_H