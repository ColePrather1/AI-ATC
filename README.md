# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB


## Install
       git clone https://github.com/ColePrather1/AI-ATC.git

## Initial setup
####    Prepare system for AI-ATC
       chmod +x initial.sh
       sudo ./initial.sh
####    Controller Auto-connect with bluetoothctl
       chmod +x bt-setup.sh
       sudo ./bt-setup.sh
       sudo reboot
    

## Compiling
       mkdir build && cd build
       cmake ..
       make

## Executing
       ./bin/AI-ATC




