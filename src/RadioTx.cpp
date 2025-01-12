#include "RadioTx.h"
#include "RadioTxQueue.h"
#include "packets/packets.h"

void sendToPlane(Packet* packet){
    RadioTx::tx_queue.enqueue(packet);
    return;
}
