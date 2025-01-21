#ifndef RADIO_TX_QUEUE_H
#define RADIO_TX_QUEUE_H
#pragma once
#include "ThreadSafeQueue.h"
#include "packets/packets.h"

namespace RadioTx {
    //ThreadSafeQueue<Packet> tx_queue;
    inline ThreadSafeQueue<Packet*> tx_queue(100);
}

#endif // RADIO_TX_QUEUE_H