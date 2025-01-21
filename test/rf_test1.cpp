#include <RF24/RF24.h>
#include <RF24/utility/SPIDEV/spi.h>
#include <iostream>
#include <thread>
#include <string>

RF24 radio0(22, 0);
RF24 radio1(23, 10);

const uint8_t pipes[][6] = {"PIPE0", "PIPE1"};
const std::string message0 = "We are the knights who say Ni!";
const std::string message1 = "Rick & Morty!";

void setup() {
    if (!radio0.begin()) {
        std::cout << "radio0 initialization failed" << std::endl;
        return;
    }
    std::cout << "radio0 initialized" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    

    if (!radio1.begin()) {
        std::cout << "radio1 initialization failed" << std::endl;
        return;
    }  
    std::cout << "radio1 initialized" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    radio0.setPALevel(RF24_PA_LOW);
    radio1.setPALevel(RF24_PA_LOW);

    radio0.openWritingPipe(pipes[0]);
    radio1.openWritingPipe(pipes[1]);

    radio0.stopListening();
    radio1.stopListening();
}

void loop() {
    // Write "hello,world" using radio0 on PIPE0
    bool ok0 = radio0.write(message0.c_str(), message0.length());
    if (ok0) {
        std::cout << "Radio0 sent message successfully" << std::endl;
    } else {
        std::cout << "Radio0 failed to send message" << std::endl;
    }

    // Write "hello,world" using radio1 on PIPE1
    bool ok1 = radio1.write(message1.c_str(), message1.length());
    if (ok1) {
        std::cout << "Radio1 sent message successfully" << std::endl;
    } else {
        std::cout << "Radio1 failed to send message" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    setup();
    while(1) {
        loop();
    }
    return 0;
}
