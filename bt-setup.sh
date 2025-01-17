#!/bin/bash

# Bluetooth Controller Auto-Connect Setup Script

WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 
CONTROLLER_MAC=$WHITE_PS5_CTLR_MAC

# Ensure script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (use sudo)"
  exit 1
fi

# Prompt for controller MAC address if not provided
if [ -z "$CONTROLLER_MAC" ]; then
  read -p "Enter your controller's MAC address (format XX:XX:XX:XX:XX:XX): " CONTROLLER_MAC
fi

# Install necessary packages
apt-get update
apt-get install -y bluetooth bluez blueman

# Create the auto-connect script
cat << EOF > /usr/local/bin/bt-autoconnect.sh
#!/bin/bash

CONTROLLER_MAC="$CONTROLLER_MAC"

while true; do
    if ! bluetoothctl info \$CONTROLLER_MAC | grep -q "Connected: yes"; then
        echo "Attempting to connect to controller..."
        bluetoothctl connect \$CONTROLLER_MAC
        if [ $? -eq 0 ]; then
            echo "Connection successful"
            # Add post-connection commands here
        else
            echo "Connection failed"
        fi
    fi
    sleep 10
done
EOF

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
RestartSec=10
User=root

[Install]
WantedBy=multi-user.target
EOF

# Configure Bluetooth settings
cat << EOF >> /etc/bluetooth/main.conf

[General]
AutoEnable=true
FastConnectable = true
Discoverable = true
DiscoverableTimeout = 0

[Policy]
AutoEnable=true
EOF


# Enable Bluetooth service
systemctl enable bluetooth.service
# Enable and start the auto-connect service
systemctl enable bt-autoconnect.service
systemctl start bt-autoconnect.service


echo "Setup complete. Please reboot your Raspberry Pi for changes to take effect."
