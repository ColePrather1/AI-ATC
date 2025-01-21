#include <SPI.h>
#include <RF24.h>

#include "nano_rf_test.h"


RF24 radio(8, 10); // CE pin 9, CSN pin 10 for Arduino
//RF24 radio;

const uint64_t pipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };


void setup() {
  Serial.begin(9600);
  //Serial.println("We started");

  //radio = RF24(8,10);
  //Serial.println("Radio created");
  
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1); // Hold in infinite loop
  }
  
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(69);
  radio.openReadingPipe(0, pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  
  radio.startListening();
  
  Serial.println("NRF24L01 receiver initialized successfully");
}

void loop() {

  Packet* pkt;
  static uint8_t pipe;
  static uint8_t pkt_size;

  PacketType pkt_type;

  //uint8_t buffer[32];

  byte buffer[32];

  if (radio.available(&pipe)) {
    pkt_size = radio.getDynamicPayloadSize();

    radio.read(buffer, pkt_size);
    //const Packet* packet = reinterpret_cast<const Packet*>(buffer);
    //pkt_type = 
    pkt_type =  reinterpret_cast<const Packet*>(buffer)->type;

    switch (pkt_type) {
      case PacketType::BASE:
        Serial.println("BASE packet received.");
        break;
      case PacketType::MANUAL:
        Serial.println("MANUAL :");
        const ManualPacket* mPkt = reinterpret_cast<const ManualPacket*>(buffer);

        uint8_t throttle = mPkt->throttle;
        uint8_t elevator = mPkt->elevator;
        uint8_t rudder = mPkt->rudder;
        uint8_t left_aileron = mPkt->left_aileron;
        uint8_t right_aileron = mPkt->right_aileron;
        Serial.println(" Throttle :");
        Serial.print(throttle);
        Serial.println(" Elevator :");
        Serial.print(elevator);
        Serial.println(" Rudder :");
        Serial.print(rudder);
        Serial.println(" Left Aileron :");
        Serial.print(left_aileron);
        Serial.println(" Right Aileron :");
        Serial.print(right_aileron);
        break;
    }




    //char text[32] = "";

    //std::vector<std::byte> buffer(incoming_packet_size);
    //radio_rx.read(buffer.data(), incoming_packet_size);
    //rx_buffer_queue.enqueue(buffer);    



    //radio.read(&text, sizeof(text));
    //Serial.print("Received: ");
    //Serial.println(text);



  }
}

