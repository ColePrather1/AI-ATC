#ifndef RF_RX_H
#define RF_RX_H
#pragma once

#include "Common.h"
#include "Session.h"
#include "rf_com.h"

#include <cstdint>

#include "include/packets/packets.h"
#define MAX_PACKET_SIZE 32

#include <array>
#include <span>

//static RF24 radio_rx; // CE, CSN pins for receiving radio

//extern RF24 radio_rx;

//static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio

// Frequenty used memory allocations
Packet incoming_packet*;


//template<size_t buffer_size>
//struct BufferItem {
//    //std::array<std::byte, buffer_size> buffer;
//    //std::span<std::byte> buffer;
//    std::span<std::byte, buffer_size> buffer;
//    //uint8_t size;
//};

ThreadSafeQueue<std::span<std::byte>> rx_buffer_queue;

//ThreadSafeQueue<BufferItem> rx_buffer_queue;

//ThreadSafeQueue<std::span<std::byte, item.size>> rx_buffer_queue;

//ThreadSafeQueue<std::array<std::byte, MAX_PACKET_SIZE>> rx_buffer_queue;

//size_t incoming_packet_size;
//PacketType incoming_packet_type;

//ThreadSafeQueue<Packet*> rx_processing_queue;

//Packet* createPacket(std::array<std::byte, incoming_packet_size> buffer) {}

//inline Packet* getPacket(std::array<std::byte, incoming_packet_size> packet_buffer);

//
//template<size_t packet_buffer_size>
//inline void procces_rx_packet(std::array<std::byte, packet_buffer_size> packet_buffer);
//inline Packet* getPacket(std::array<std::byte, packet_buffer_size> packet_buffer);

//template<size_t packet_buffer_size>
//inline void procces_rx_packet(std::array<std::byte, packet_buffer_size> packet_buffer);

//template<size_t packet_buffer_size>
//inline void enqueue_rx_buffer(std::array<std::byte, packet_buffer_size> packet_buffer){
//    rx_buffer_queue.enqueue(packet_buffer);
//}



bool rx_setup() {
    // Initialize receiving radio
    //RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
    RF24 radio_rx(23, 10); // CE, CSN pins for receiving radio
    if (!radio_rx.begin()) {
        std::cout << "Failed to initialize receiving radio" << std::endl;
        return false;
    }
    radio_rx.openReadingPipe(1, pipes[5]); // Use pipe 5 for receiving
    radio_rx.setChannel(69);
    radio_rx.setPALevel(RF24_PA_LOW);
    radio_rx.setAutoAck(false);
    radio_rx.setDataRate(RF24_250KBPS);
    radio_rx.startListening();
    return true;
}


/*
TODO: Implement, time to get real
*/
void rx_loop() {
    if (radio_rx.available()) {

    // Get the size of the packet
        uint8_t incoming_packet_size = radio_rx.getDynamicPayloadSize();

    // Check packet size
        if (incoming_packet_size > MAX_PACKET_SIZE) {
            std::cerr << "Received packet size exceeds maximum" << std::endl;
            radio_rx.flush_rx(); // Clear the RX FIFO
            return;
        }
    // Send to processing
        //std::array<std::byte, incoming_packet_size> buffer;
        //BufferItem<incoming_packet_size> buffer;
        //buffer.size = incoming_packet_size;
        //std::span<std::byte> buffer = std::span<std::byte>(std::make_unique<std::byte[]>(incoming_packet_size), incoming_packet_size);
        std::span<std::byte> buffer;
        radio_rx.read(buffer.data(), incoming_packet_size);
        rx_buffer_queue.enqueue();    

    }   
}


template<size_t packet_buffer_size>
inline void procces_rx_packet(std::array<std::byte, packet_buffer_size> packet_buffer){
    reinterpret_cast<Packet*>(packet_buffer.data())->process();
    return;

    /*
    incoming_packet_type = static_cast<PacketType>(buffer[0]);

    switch (incoming_packet_type) {
        case PacketType::SYSTEM:
            return reinterpret_cast<SystemPacket*>(packet_buffer.data());
        //case PacketType::STATUS:
        //    return reinterpret_cast<StatusPacket*>(packet_buffer.data());
        case PacketType::PAIRING:
            return reinterpret_cast<PairedPacket*>(packet_buffer.data());
        case PacketType::ACK:
            return reinterpret_cast<ACKPacket*>(packet_buffer.data());        
        case PacketType::EVENT:
            return reinterpret_cast<EventPacket*>(packet_buffer.data());
        case PacketType::EVENT_DATA:
            return reinterpret_cast<EventDataPacket*>(packet_buffer.data());
        case PacketType::EVENT_TIMED:
            return reinterpret_cast<EventTimedPacket*>(packet_buffer.data());
        case PacketType::EVENT_TIMED_DATA:
            return reinterpret_cast<EventTimedDataPacket*>(packet_buffer.data());
        case PacketType::AUTO:
            return reinterpret_cast<AutoPacket*>(packet_buffer.data());
        case PacketType::ASSIST:
            return reinterpret_cast<AssistPacket*>(packet_buffer.data());
        case PacketType::MANUAL:
            return reinterpret_cast<ManualPacket*>(packet_buffer.data());
        case PacketType::GPS:
            return reinterpret_cast<GpsPacket*>(packet_buffer.data());
        case PacketType::GPS_ENV:
            return reinterpret_cast<GpsEnvPacket*>(packet_buffer.data());
        case PacketType::GPS_ENV_DATA:
            return reinterpret_cast<GpsEnvDataPacket*>(packet_buffer.data());
        case PacketType::ACCEL:
            return reinterpret_cast<AccelPacket*>(packet_buffer.data());
        case PacketType::GYRO:
            return reinterpret_cast<GyroPacket*>(packet_buffer.data());
        case PacketType::MAGNET:
            return reinterpret_cast<MagnetPacket*>(packet_buffer.data());
        case PacketType::BARO:
            return reinterpret_cast<BaroPacket*>(packet_buffer.data());
        case PacketType::EMERGENCY:
            return reinterpret_cast<EmergencyPacket*>(packet_buffer.data());
        case PacketType::DEBUG:
            return reinterpret_cast<DebugPacket*>(packet_buffer.data());
        default:
            std::cout << "Unknown packet type" << std::endl;
            return;
    }   
    */
}


/*

void rx_loop() {
    //Packet incoming_packet;
    if (radio_rx.available()) {

        // Get the size of the packet
        incoming_packet_size = radio_rx.getDynamicPayloadSize();

        // Check packet size
        if (incoming_packet_size > MAX_PACKET_SIZE) {
            std::cerr << "Received packet size exceeds maximum" << std::endl;
            radio_rx.flush_rx(); // Clear the RX FIFO
            return;
        }

    
        //std::array<uint8_t> buffer(incoming_packet_size);
        //radio_rx.read(buffer.data(), incoming_packet_size);
        //Packet* incoming_packet = reinterpret_cast<Packet*>(buffer);
        //PacketType packet_type = incoming_packet->type;







//TODO: Verify this works , byte

        // Make global after testing
        //uint8_t buffer[sizeof(MAX_PACKET_SIZE)];
        //uint8_t buffer[incoming_packet_size];
        //std::byte[32] buffer;
        //std::byte buffer[incoming_packet_size];
        //std::array<uint8_t, incoming_packet_size> buffer;

        //Packet incoming_packet*;
        // Read the packet
        std::array<std::byte, incoming_packet_size> buffer;
        radio_rx.read(buffer, incoming_packet_size);
        procces_rx_packet(buffer);
        //incoming_packet_type = static_cast<PacketType>(buffer[0]);
        //incoming_packet = createPacket(buffer);
        //incoming_packet->process();
        //incoming_packet_type = reinterpret_cast<PacketType>(buffer[0]);
        //incoming_packet = reinterpret_cast<Packet*>(buffer);

        //incoming_packet->process();

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

        
        //if (!free_packets.empty()) {
        //    Packet* incoming_packet = free_packets.front();
        //    free_packets.pop();
        //    
        //    incoming_packet->deserialize(rx_buffer.data(), packet_size);
        //    Session::rx_queue.enqueue(incoming_packet);
        //} else {
        //    std::cerr << "Packet pool exhausted" << std::endl;
        //}
        

        


        // Process the received data as needed
        //process_rx_packet(incoming_packet);


        // Parse the received data into a DataPacket struct


        // Send to processing
        //Session::rx_processing_queue.enqueue(incoming_packet);

    }   
}
*/


/*
std::array<std::byte, incoming_packet_size> rx_buffer;
template<size_t packet_buffer_size>
inline Packet* getPacket(std::array<std::byte, packet_buffer_size> packet_buffer){
    incoming_packet_type = static_cast<PacketType>(buffer[0]);

    switch (incoming_packet_type) {
        case PacketType::SYSTEM:
            return reinterpret_cast<SystemPacket*>(packet_buffer.data());
        //case PacketType::STATUS:
        //    return reinterpret_cast<StatusPacket*>(packet_buffer.data());
        case PacketType::PAIRING:
            return reinterpret_cast<PairedPacket*>(packet_buffer.data());
        case PacketType::ACK:
            return reinterpret_cast<ACKPacket*>(packet_buffer.data());        
        case PacketType::EVENT:
            return reinterpret_cast<EventPacket*>(packet_buffer.data());
        case PacketType::EVENT_DATA:
            return reinterpret_cast<EventDataPacket*>(packet_buffer.data());
        case PacketType::EVENT_TIMED:
            return reinterpret_cast<EventTimedPacket*>(packet_buffer.data());
        case PacketType::EVENT_TIMED_DATA:
            return reinterpret_cast<EventTimedDataPacket*>(packet_buffer.data());
        case PacketType::AUTO:
            return reinterpret_cast<AutoPacket*>(packet_buffer.data());
        case PacketType::ASSIST:
            return reinterpret_cast<AssistPacket*>(packet_buffer.data());
        case PacketType::MANUAL:
            return reinterpret_cast<ManualPacket*>(packet_buffer.data());


    }
    //return reinterpret_cast<Packet>(packet_buffer.data())
}
*/


/*
bool process_rx_packet(Packet* packet) {
    switch (packet->type) {
        case PacketType::SYSTEM:
        case PacketType::STATUS:
        case PacketType::PAIRING:
        case PacketType::ACK:
            return 0;

        case PacketType::AUTO:
            return 1;
        
        case PacketType::ASSIST:
        case PacketType::MANUAL:
            return 2;

        case PacketType::ACCEL:
        case PacketType::GYRO:
        case PacketType::MAGNET:
            return 3;

        case PacketType::GPS:
        case PacketType::GPS_ENV:
            return 4;
        
        case PacketType::BAROMETER:
        case PacketType::TEMP_HUMID:
        //case PacketType::SENSOR_PACKET:
            return 5;

        case PacketType::BASE:                      // No Pipe / Error Handling
        default:
            return -1;
    }
}
*/


#endif // RF_RX_H