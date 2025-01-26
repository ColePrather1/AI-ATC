#!/bin/bash

# Bluetooth Controller Auto-Connect Setup Script

#WHITE_PS5_CTLR_MAC="7C:66:EF:28:79:D0" 
#CONTROLLER_MAC=$WHITE_PS5_CTLR_MAC


# Ensure script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (use sudo)"
  exit 1
fi

sudo usermod -a -G bluetooth $USER


# Prompt for controller MAC address if not provided
#if [ -z "$CONTROLLER_MAC" ]; then
#  read -p "Enter your controller's MAC address (format XX:XX:XX:XX:XX:XX): " CONTROLLER_MAC
#fi

# Install necessary packages
sudo apt-get update
sudo apt-get install -y bluetooth bluez blueman

# Copy the auto-connect script
cp bt-autoconnect.sh /usr/local/bin/bt-autoconnect.sh
chmod +x /usr/local/bin/bt-autoconnect.sh

## Copy the boot script
#cp boot.sh /usr/local/bin/boot.sh
#chmod +x /usr/local/bin/boot.sh


#cp boot.service /etc/systemd/system/boot.service
cp bt-autoconnect.service /etc/systemd/system/bt-autoconnect.service
cp bt_main.conf /etc/bluetooth/main.conf
cp 90-bt-autoconnect.rules /etc/udev/rules.d/90-bt-autoconnect.rules
sudo cp my_RF24.h /usr/local/include/RF24/RF24.h
sudo cp my_spi.h /usr/local/include/RF24/utility/SPIDEV/spi.h

# Enable Bluetooth service
systemctl enable bluetooth.service
systemctl enable bt-autoconnect.service
#systemctl start bt-autoconnect.service

echo "Bluetooth setup complete. Please reboot your Raspberry Pi for changes to take effect."
