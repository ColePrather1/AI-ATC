#ifndef PI_BLE_H
#define PI_BLE_H
#pragma once

#include <cstdlib>

inline void enable_ble(){
    //system("sudo hciconfig hci0 piscan");
    system("sudo bluetoothctl power on");
    system("agent on default-agent");
    system("scan on");
    system("connect 7C:66:EF:28:79:D0");
}

#endif // PI_BLE_H