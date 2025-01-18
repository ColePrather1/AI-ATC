#!/bin/bash
#CONTROLLER_MAC_ADDRESS = "7C:66:EF:28:79:D0"

# Configure Bluetooth
echo "Configuring Bluetooth..."
sudo bluetoothctl << EOF
power on
agent on
default-agent
scan on
pairable on
#pair DualSense
#connect DualSense
trust DualSense
EOF

echo "Setup complete!"