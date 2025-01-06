#ifndef RADIO_H
#define RADIO_H

#pragma once

#include "Common.h"
#include "Session.h"
#include "packets.h"



/*
    Receive from plane
*/
bool getFromPlane(Packet& packet){
    //Session::rx_queue.dequeue(packet);
    radio_rx.read(&incoming_packet, sizeof(incoming_packet));
    Session::rx_queue.enqueue(packet);
    return true;
}



/*
    Transmit to plane
*/
void sendToPlane(Packet& packet){
    Session::tx_queue.enqueue(packet);
    return;
}




#endif // RADIO_H