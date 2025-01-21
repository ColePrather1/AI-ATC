#include <iostream>
#include <hidapi/hidapi.h>
#include <cstring>
#include <unistd.h>

#define SONY_VID 0x054C
#define DUALSENSE_PID 0x0CE6

int main() {
    // Initialize the HIDAPI library
    if (hid_init() != 0) {
        std::cerr << "Failed to initialize HIDAPI" << std::endl;
        return 1;
    }

    // Open the DualSense controller
    hid_device *device = hid_open(SONY_VID, DUALSENSE_PID, NULL);
    if (!device) {
        std::cerr << "Failed to open DualSense controller" << std::endl;
        hid_exit();
        return 1;
    }

    unsigned char buf[64];
    while (true) {
        // Read input report from the controller
        int res = hid_read(device, buf, sizeof(buf));
        if (res < 0) {
            std::cerr << "Error reading from device" << std::endl;
            break;
        }

        // Parse and print button states
        if (res >= 8) {
            std::cout << "Cross: " << ((buf[8] & 0x20) ? "Pressed" : "Released") << std::endl;
            std::cout << "Circle: " << ((buf[8] & 0x40) ? "Pressed" : "Released") << std::endl;
            std::cout << "Triangle: " << ((buf[8] & 0x80) ? "Pressed" : "Released") << std::endl;
            std::cout << "Square: " << ((buf[8] & 0x10) ? "Pressed" : "Released") << std::endl;

            // Left stick X and Y (0-255)
            std::cout << "Left Stick X: " << (int)buf[1] << std::endl;
            std::cout << "Left Stick Y: " << (int)buf[2] << std::endl;

            // Right stick X and Y (0-255)
            std::cout << "Right Stick X: " << (int)buf[3] << std::endl;
            std::cout << "Right Stick Y: " << (int)buf[4] << std::endl;

            std::cout << "-------------------" << std::endl;
        }

        usleep(16667); // ~60 Hz refresh rate
    }

    // Close the device and exit
    hid_close(device);
    hid_exit();
    return 0;
}