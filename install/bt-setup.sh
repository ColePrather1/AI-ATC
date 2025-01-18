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

# Copy the auto-connect script
cp bt-autoconnect.sh /usr/local/bin/bt-autoconnect.sh
chmod +x /usr/local/bin/bt-autoconnect.sh

cp bt-autoconnect.service /etc/systemd/system/bt-autoconnect.service
cp new_main.conf /etc/bluetooth/main.conf
cp 90-bt-autoconnect.rules /etc/udev/rules.d


# Enable Bluetooth service
systemctl enable bluetooth.service
# Enable and start the auto-connect service
systemctl enable bt-autoconnect.service
systemctl start bt-autoconnect.service


echo "Setup complete. Please reboot your Raspberry Pi for changes to take effect."
