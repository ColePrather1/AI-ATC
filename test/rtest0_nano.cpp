#include <SPI.h>
#include <RF24.h>

RF24 radio(8, 10); // CE pin 9, CSN pin 10 for Arduino

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1); // Hold in infinite loop
  }
  
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(76);
  radio.openReadingPipe(0, address);
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