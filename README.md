# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB


## Install
       git clone https://github.com/ColePrather1/AI-ATC.git

## Initial setup
## Required Tools
####  1) Allow execution rights of .sh script
       chmod +x initial.sh
####  2) Run with sudo
       sudo ./initial.sh

### Bluetoothctl controller Auto-connect
####  1) Allow execution rights of .sh script & Run with sudo & Reboot
       chmod +x bt-setup.sh
       sudo ./bt-setup.sh
       sudo reboot
    

## Compiling
       mkdir build && cd build
       cmake ..
       make

## Executing
       ./bin/AI-ATC




