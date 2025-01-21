#include <RF24/RF24.h>
#include <RF24/utility/SPIDEV/spi.h>

#include <iostream>
#include <thread>

//dtparam=spi=on
//dtoverlay=spi1-3cs


//g++ -o dual_radio_test dual_radio_test.cpp -lrf24


//SPI spi0, spi1;
//RF24 radio(CE, CSN)
//RF24 radio0(8, 22);  // CE pin 22, CSN pin 0 (SPI0)
//RF24 radio0(22, 8);  // CE pin 22, CSN pin 0 (SPI0)
//RF24 radio1(23, 18);  // CE pin 23, CSN pin 1 (SPI1)

RF24 radio0(22, 0);
RF24 radio1(23, 10);
//RF24 radio1(23, 1);

void setup() {
    // Initialize SPI buses
    //spi0.begin(0);  // SPI0
    //spi1.begin(1);  // SPI1

    // Initialize radios with their respective SPI buses
    //radio0.begin(&spi0);
    //radio1.begin(&spi1);

    //radio0.spi = spi0;
    //std::cout << "radio0 set" << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //radio1.spi = spi1;
    //std::cout << "radio1 set" << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //radio0.begin();



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

    // Configure radios...
    radio0.setPALevel(RF24_PA_LOW);
    radio1.setPALevel(RF24_PA_LOW);
    // ... other configurations
}

void loop() {
    // Use radio0 and radio1 for communication
}

int main() {
    setup();
    while(1) {
        loop();
    }
    return 0;
}
