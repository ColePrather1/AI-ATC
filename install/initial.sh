#!/bin/bash

#CONTROLLER_MAC_ADDRESS = "7C:66:EF:28:79:D0"
#set-alias 7C:66:EF:28:79:D0 DualSense

# Ensure script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run as root (use sudo)"
  exit 1
fi


set -e

# Function to check if a command exists
command_exists() {
    command -v "$1" &> /dev/null
}

# Function to install a package if not already installed
install_package() {
    if ! dpkg -s "$1" &> /dev/null; then
        echo "Installing $1..."
        sudo apt install -y "$1"
    else
        echo "$1 is already installed."
    fi
}

# Update package lists
echo "Updating package lists..."
sudo apt update -y

# Install essential build tools
echo "Installing essential build tools..."
sudo apt install -y build-essential cmake git

# Install SQLite3 & SDL2
install_package "sqlite3"
install_package "libsqlite3-dev"
install_package "libsdl2-dev"
#install_package ""

# Install RF24 library
if [ ! -d "/usr/local/include/RF24" ]; then
    echo "Installing RF24 library..."
    git clone https://github.com/tmrh20/RF24.git
    cd RF24 || exit
    ./configure
    make
    sudo make install
    cd .. || exit
    rm -rf RF24
else
    echo "RF24 library is already installed."
fi



# Enable SPI
echo "Enabling SPI..."
if command_exists raspi-config; then
    sudo raspi-config nonint do_spi 0
else
    echo "raspi-config not found. Please enable SPI manually."
fi


# Configure Bluetooth
chmod +x bt-setup.sh
sudo ./bt-setup.sh


echo "Setup complete!"
