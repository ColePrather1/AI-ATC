
//g++ rtest0.cpp -o rtest -lrf24
#include <RF24/RF24.h>
#include <iostream>

using namespace std;

RF24 radio(22, 0); // CE pin 22, CSN pin 0 (CE0)

//const uint8_t address[6] = "00001";

const uint64_t pipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };


int main() {
    if (!radio.begin()) {
        cout << "Radio hardware not responding!" << endl;
        return 1;
    }

    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(pipes[0]);
    
    //radio.setChannel(76);
    //radio.openWritingPipe(address);

    cout << "NRF24L01 initialized successfully" << endl;

    while (true) {
        const char text[] = "Hello World";
        if (!radio.write(&text, sizeof(text))) {
            cout << "Failed to send data" << endl;
            continue;
        }
        cout << "Sent: " << text << endl;
        delay(1000);
    }

    return 0;
}
