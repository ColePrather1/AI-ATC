









# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB

# Requirements

For compilation & execution

- [Raspberry Pi 3/4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)

- [Raspberry Pi OS (latest version recommended)](https://www.raspberrypi.com/software/) 
 
- [SDL2](https://www.libsdl.org/)
 
- [SQLite3](https://www.sqlite.org/)
 
- [RF24](https://github.com/nRF24/RF24)

- C++17 compatible compiler

- [CMake](https://cmake.org/)

- [Git](https://git-scm.com/)
 

For development:
  
- [GCC or Clang](https://gcc.gnu.org/) (for compilation)
  
- [GDB](https://www.gnu.org/software/gdb/) (for debugging)
  

# How to use

1. Clone this repository 
       
       git clone https://github.com/ColePrather1/AI-ATC.git
       
2. Run inital setup script
       
       cd AI-ATC
       chmod +x install/initial.sh
       sudo ./install/initial.sh
            
3. Reboot to apply changes

       sudo reboot

4. Compilation

       cd AI-ATC
       mkdir build && cd build
       cmake ..
       make

- To recompile, first clean the build directory:

       rm -rf *

5. Execution

       ./bin/AI-ATC


# Contributing
Contributions are welcome! Please feel free to submit a Pull Request.





## Initial setup
#### Prepare system for AI-ATC
       chmod +x install/initial.sh
       sudo ./install/initial.sh
##### Reboot to apply changes

## Compilation
##### Create and navigate to the build directory:
       mkdir build && cd build
##### Generate the build files and compile:
       cmake ..
       make
##### To recompile, first clean the build directory:
       rm -rf *

# Execution
       ./bin/AI-ATC


# Contributing
Contributions are welcome! Please feel free to submit a Pull Request.







# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB


sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install wiringpi
sudo apt-get install g++ RF24 

cd ~/'Pi 3b+ Base'

cd ~/rf24libs

g++ -o atc atc.cpp -lRF24 -lSDL2

g++ -o atc atc.cpp -L/home/atc/ -lRF24 -lSDL2


g++ -o atc atc.cpp -I/usr/local/include -L/usr/local/lib -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/include -L/home/atc/ -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/include -L/home/atc/rf24libs -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/lib -L/home/atc/rf24libs -lRF24 -lSDL2

///////////////////////////////////
g++ -o atc atc.cpp -I/usr/local/lib -L/home/atc/rf24libs -lrf24 -lSDL2


7C:66:EF:28:79:D0


cd /'Pi 3b+ Base'/ && sudo ./atc


//////////////////////////////////////////

g++ ctest.cpp -o ctest -lhidapi-libusb


sudo bluetoothctl

agent on
default-agent

scan on

connect 7C:66:EF:28:79:D0


////////////////////////////////////////

## Install
       git clone https://github.com/ColePrather1/AI-ATC.git

## Initial setup


## Bluetoothctl controller Auto-connect

####  1) Allow execution rights of .sh script
       chmod +x bt-setup.sh
####  3) Run with sudo
       sudo ./bt-setup.sh
####  4) Reboot to take affect
       sudo reboot
    

## Compiling
       mkdir build && cd build
       cmake ..
       make

## Executing
       ./bin/AI-ATC




#### Controller Auto-connect with bluetoothctl
       chmod +x bt-setup.sh
       sudo ./bt-setup.sh
       sudo reboot