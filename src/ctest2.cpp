#include <iostream>
#include <cstring>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

struct DualSenseState {
    uint8_t leftStickX;
    uint8_t leftStickY;
    uint8_t rightStickX;
    uint8_t rightStickY;
    uint8_t l2Trigger;
    uint8_t r2Trigger;
    uint8_t buttons[4];
};

void parseDualSenseInput(const unsigned char* data, DualSenseState& state) {
    if (data[0] == 0xa1 && data[1] == 0x01) {
        state.leftStickX = data[2];
        state.leftStickY = data[3];
        state.rightStickX = data[4];
        state.rightStickY = data[5];
        state.l2Trigger = data[6];
        state.r2Trigger = data[7];
        memcpy(state.buttons, &data[8], 4);
    }
}

void printDualSenseState(const DualSenseState& state) {
    std::cout << "Left Stick: (" << (int)state.leftStickX << ", " << (int)state.leftStickY << ")" << std::endl;
    std::cout << "Right Stick: (" << (int)state.rightStickX << ", " << (int)state.rightStickY << ")" << std::endl;
    std::cout << "L2 Trigger: " << (int)state.l2Trigger << std::endl;
    std::cout << "R2 Trigger: " << (int)state.r2Trigger << std::endl;
    std::cout << "Buttons: ";
    for (int i = 0; i < 4; i++) {
        std::cout << std::hex << (int)state.buttons[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    int dev_id = hci_get_route(NULL);
    int sock = hci_open_dev(dev_id);

    if (dev_id < 0 || sock < 0) {
        std::cerr << "Error opening HCI device." << std::endl;
        return 1;
    }

    struct hci_filter flt;
    hci_filter_clear(&flt);
    hci_filter_set_ptype(HCI_EVENT_PKT, &flt);
    hci_filter_all_events(&flt);
    setsockopt(sock, SOL_HCI, HCI_FILTER, &flt, sizeof(flt));

    unsigned char buf[HCI_MAX_EVENT_SIZE];
    DualSenseState state;

    while (true) {
        int len = read(sock, buf, sizeof(buf));
        if (len > 0) {
            evt_le_meta_event* meta = (evt_le_meta_event*)(buf + (1 + HCI_EVENT_HDR_SIZE));
            le_advertising_info* info = (le_advertising_info*)(meta->data + 1);

            if (info->length == 11) {
                parseDualSenseInput(info->data, state);
                printDualSenseState(state);
            }
        }
    }

    close(sock);
    return 0;
}
