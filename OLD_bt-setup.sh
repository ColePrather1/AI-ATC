#!/bin/bash

# Bluetooth Controller Auto-Connect Setup Script
# This script automates the process of setting up auto-connection for a Bluetooth controller on a Raspberry Pi.

# Ensure script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (use sudo)"
  exit 1
fi


WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 
CONTROLLER_MAC=$WHITE_PS5_CTLR_MAC
# Prompt for controller MAC address
#read -p "Enter your controller's MAC address (format XX:XX:XX:XX:XX:XX): " CONTROLLER_MAC


# Create the auto-connect script
cat << EOF > /usr/local/bin/bt-autoconnect.sh
#!/bin/bash

CONTROLLER_MAC="$CONTROLLER_MAC"

while true; do
    if bluetoothctl info \$CONTROLLER_MAC | grep -q "Connected: no"; then
        echo "Attempting to connect to controller..."
        bluetoothctl connect \$CONTROLLER_MAC
    fi
    sleep 10
done
EOF

# Make the script executable
chmod +x /usr/local/bin/bt-autoconnect.sh

# Create the systemd service file

cat << EOF > /etc/systemd/system/bt-autoconnect.service
[Unit]
Description=Bluetooth Controller Auto-connect
After=bluetooth.service
Wants=bluetooth.service

[Service]
ExecStart=/usr/local/bin/bt-autoconnect.sh
Restart=always

[Install]
WantedBy=multi-user.target
EOF

# Enable and start the service
systemctl enable bt-autoconnect.service
systemctl start bt-autoconnect.service

# Configure Bluetooth settings
cat << EOF >> /etc/bluetooth/main.conf

[General]
FastConnectable = true
#AutoEnable=true    # Already 

[Policy]
AutoEnable=true
EOF

echo "Setup complete. Please reboot your Raspberry Pi for changes to take effect."
