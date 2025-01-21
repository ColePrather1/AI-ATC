#!/bin/bash

WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 
CONTROLLER_MAC=$WHITE_PS5_CTLR_MAC
CONTROLLER_MAC="$CONTROLLER_MAC"

while true; do
    if ! bluetoothctl info $CONTROLLER_MAC | grep -q "Paired: yes"; then
        echo "Attempting to pair to controller..."
        
        # Pair the controller
        if ! bluetoothctl pair $CONTROLLER_MAC; then
            sleep 2 
            if bluetoothctl info $CONTROLLER_MAC | grep -q "pair: yes"; then
                bluetoothctl trust $CONTROLLER_MAC
                echo "Pair successful"
                # Add post-pair commands here
            fi




            
        else
            echo "Pair failed"
        fi
    fi
    sleep 10
done


#pair "7C:66:EF:28:79:D0"
#connect "7C:66:EF:28:79:D0"
#trust "7C:66:EF:28:79:D0"
#set-alias DualSense

