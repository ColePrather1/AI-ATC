#ifndef THREAD_RF_RX_H
#define THREAD_RF_RX_H

#pragma once
#include "Common.h"
#include "Session.h"
#include "QuickThread.h"
#include "rf_rx.h"

#include <array>
#include <iostream>
#include <bit>


//static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio

static bool rf_rx_setup(){
    /*
    // Initialize receiving radio
    //RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
    if (!radio_rx.begin()) {
        std::cout << "Failed to initialize receiving radio" << std::endl;
        return false;
    }
    radio_rx.openReadingPipe(1, pipes[5]); // Use pipe 5 for receiving
    radio_rx.setPALevel(RF24_PA_LOW);
    radio_rx.startListening();
    return true;
    */

    return rx_setup();


}


/*
TODO: Implement, time to get real
*/
//Packet* incoming_packet;
//Packet incoming_packet;

#define MAX_PACKET_SIZE 32

static void rf_rx_loop(){
    //Packet incoming_packet;
    if (radio_rx.available()) {

        // Get the size of the packet
        incoming_packet_size = radio_rx.getDynamicPayloadSize();

        // Check packet size
        if (packet_size > MAX_PACKET_SIZE) {
            std::cerr << "Received packet size exceeds maximum" << std::endl;
            radio_rx.flush_rx(); // Clear the RX FIFO
            return;
        }

    
        //std::array<uint8_t> buffer(incoming_packet_size);
        //radio_rx.read(buffer.data(), incoming_packet_size);
        //Packet* incoming_packet = reinterpret_cast<Packet*>(buffer);
        //PacketType packet_type = incoming_packet->type;






/*
TODO: Verify this works , byte
*/
        // Make global after testing
        //uint8_t buffer[sizeof(MAX_PACKET_SIZE)];
        //uint8_t buffer[incoming_packet_size];
        //std::byte[32] buffer;
        std::byte[incoming_packet_size] buffer;
        Packet* incoming_packet;
        PacketType packet_type;
        // Read the packet
        radio_rx.read(buffer, incoming_packet_size);
        incoming_packet = reinterpret_cast<Packet*>(buffer);

        //incoming_packet->process();
/*
TODO: Would prefer adding to queue instead of processing here
*/
        //incoming_packet->process();

        //packet_type = incoming_packet->type;
        //incoming_packet = createPacket(buffer);

        



        std::cout << "Packet size: " << incoming_packet_size << std::endl;
        std::cout << "Packet type: " << (int)incoming_packet->type << std::endl;


        //PacketType packet_type = incoming_packet->type;

       //uint8_t buffer[incoming_packet_size];

        //radio_rx.read(incoming_packet, incoming_packet_size);

        //char received_data[PAYLOAD_SIZE];
        //radio_rx.read(&received_data, sizeof(received_data));
        //std::cout << "Received from plane: " << received_data << std::endl;

        // Create a new packet
        //Packet* incoming_packet = new Packet();
        //Packet* incoming_packet;

        // Get the packet
        //radio_rx.read(&incoming_packet, incoming_packet_size);
        //radio_rx.read(incoming_packet, incoming_packet_size);

    



        //Session::rx_queue.enqueue(incoming_packet);

        /*
        if (!free_packets.empty()) {
            Packet* incoming_packet = free_packets.front();
            free_packets.pop();
            
            incoming_packet->deserialize(rx_buffer.data(), packet_size);
            Session::rx_queue.enqueue(incoming_packet);
        } else {
            std::cerr << "Packet pool exhausted" << std::endl;
        }
        */

        


        // Process the received data as needed
        //process_rx_packet(incoming_packet);


        // Parse the received data into a DataPacket struct


        // Send to processing
        Session::rx_processing_queue.enqueue(incoming_packet);

    }   
}



/*

static void rf_rx_loop(){
    Packet incoming_packet;
    if (radio_rx.available()) {

        // Get the size of the packet
        incoming_packet_size = radio_rx.getDynamicPayloadSize();

        //char received_data[PAYLOAD_SIZE];
        //radio_rx.read(&received_data, sizeof(received_data));
        //std::cout << "Received from plane: " << received_data << std::endl;

        // Get the packet
        radio_rx.read(&incoming_packet, sizeof(incoming_packet));
        // Send to processing by type
        Session::rx_queue.enqueue(incoming_packet);



        

        // Process the received data as needed
        //process_rx_packet(incoming_packet);


        // Parse the received data into a DataPacket struct

    }
    //usleep(10000);
    
}

*/


extern QuickThread rf_rx_thread(rf_rx_setup, rf_rx_loop);

#endif // THREAD_RF_RX_H