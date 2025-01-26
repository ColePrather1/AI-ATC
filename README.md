# AI-ATC
AI-ATC is an innovative project that integrates artificial intelligence with RC air traffic control, designed to run on a Raspberry Pi 4 Model B 8GB.

# Requirements

For compilation & execution

- [Raspberry Pi 3/4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)

- [Raspberry Pi OS (latest 64-bit version recommended)](https://www.raspberrypi.com/software/) 
 
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
       cd AI-ATC
       
2. Run inital setup script
       
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
