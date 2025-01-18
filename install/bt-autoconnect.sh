#!/bin/bash

WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 
CONTROLLER_MAC=$WHITE_PS5_CTLR_MAC
CONTROLLER_MAC="$CONTROLLER_MAC"


setup_bluetooth() {
    # Check if Bluetooth is blocked
    if rfkill list bluetooth | grep -q "Soft blocked: yes"; then
        echo "Unblocking Bluetooth..."
        sudo rfkill unblock bluetooth
    fi

    # Check if Bluetooth service is running
    if ! systemctl is-active --quiet bluetooth; then
        echo "Starting Bluetooth service..."
        sudo systemctl start bluetooth
        sleep 2  # Wait for the service to start
    fi

    # Power on Bluetooth
    echo "Powering on Bluetooth..."
    bluetoothctl power on
}


setup_bluetooth

while true; do
    if ! bluetoothctl info $CONTROLLER_MAC | grep -q "Connected: yes"; then
        echo "Attempting to connect to controller..."
        
        if bluetoothctl connect $CONTROLLER_MAC; then
            sleep 2 
            if bluetoothctl info $CONTROLLER_MAC | grep -q "Connected: yes"; then
                echo "Connection successful"
                # Add post-connection commands here
            fi
        else
            echo "Connection failed"
        fi
    fi
    sleep 10
done


#pair "7C:66:EF:28:79:D0"
#connect "7C:66:EF:28:79:D0"
#trust "7C:66:EF:28:79:D0"
#set-alias DualSense

