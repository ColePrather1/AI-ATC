#include "threads/thread_rf_rx.hpp"
//#include "rf_rx.h"

//#include "Common.h"
//#include "Session.h"
#include "rf_com.h"

#include <cstdint>

#include "packets/packets.h"
#define MAX_PACKET_SIZE 32

#include <array>
#include <vector>
#include "ThreadSafeQueue.h"

#include "threads/rx_processesing_queue.hpp"
#include <iostream>
#include "Logging.h"
#include "myTime.h"

//static RF24 radio_rx; // CE, CSN pins for receiving radio
static RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
Packet* incoming_packet;
//ThreadSafeQueue<std::span<std::byte>> rx_buffer_queue;

static bool rf_rx_setup(){
    //return rx_setup();
    // Initialize receiving radio
    //RF24 radio_rx(23, 1); // CE, CSN pins for receiving radio
    if (!radio_rx.begin()) {
        Logging::insertEventLog(EventType::RF_RX_FAILED_TO_START);
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


static void rf_rx_loop(){
    std::cout << "rf_rx_loop has started" << std::endl;
    Logging::insertEventLog(EventType::RF_RX_LOOPED);
    //rx_loop();
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
        //std::span<std::byte> buffer;
        std::vector<std::byte> buffer(incoming_packet_size);
        radio_rx.read(buffer.data(), incoming_packet_size);
        rx_buffer_queue.enqueue(buffer);    

    }   
}


extern QuickThread rf_rx_thread(rf_rx_setup, rf_rx_loop);