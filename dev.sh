#!/bin/bash

CONTROLLER_MAC_ADDRESS="7C:66:EF:28:79:D0"
#set-alias 7C:66:EF:28:79:D0 DualSense

#pair DualSense
#connect DualSense
#trust DualSense

#sudo systemctl restart bluetooth

# Configure Bluetooth
echo "Configuring Bluetooth..."
sudo bluetoothctl << EOF
power on
agent on
default-agent
scan on
pairable on
pair $CONTROLLER_MAC_ADDRESS
connect $CONTROLLER_MAC_ADDRESS
trust $CONTROLLER_MAC_ADDRESS
EOF

echo "Setup complete!"
