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
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Received: ");
    Serial.println(text);
  }
}