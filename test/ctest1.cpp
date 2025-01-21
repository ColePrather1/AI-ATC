#include <iostream>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main() {
    int dev_id = hci_get_route(NULL);
    int sock = hci_open_dev(dev_id);
    
    if (dev_id < 0 || sock < 0) {
        std::cerr << "Error opening Bluetooth device" << std::endl;
        return 1;
    }

    // Add code here to read input from the DualSense controller
    // This will involve setting up a connection and reading from the appropriate HID report

    //close(sock);
    return 0;
}
