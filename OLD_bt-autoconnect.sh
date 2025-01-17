#!/bin/bash

# 1) Create .sh script file
#sudo nano /usr/local/bin/bt-autoconnect.sh

# 2) Allow execution rights of .sh script
#sudo chmod +x /usr/local/bin/bt-autoconnect.sh

# 3) Create a new Systemd .service file
#sudo nano /etc/systemd/system/bt-autoconnect.service

# 4) Enable the service

#CONTROLLER_MAC="XX:XX:XX:XX:XX:XX"
WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 

while true; do
    if bluetoothctl info $WHITE_PS5_CTLR_MAC_MAC | grep -q "Connected: no"; then
        echo "Attempting to connect to controller..."
        bluetoothctl connect $WHITE_PS5_CTLR_MAC
    fi
    sleep 10
done
