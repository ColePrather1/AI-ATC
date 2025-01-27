# AI-ATC


<p align="center">
  <a href="https://ColePrather.com">
    <img alt="AI-ATC Social Media Preview" src="https://raw.githubusercontent.com/ColePrather1/AI-ATC/resources/thumbnail.png" width="100%" />
  </a>
</p>

![Alt text](/resources/thumbnail.png)

![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)
[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)



AI-ATC is an innovative project that integrates artificial intelligence with RC air traffic control, designed to run on a Raspberry Pi 4 Model B 8GB. [WORK IN PROGRESS]

## Requirements

### Compilation & Execution:

- [Raspberry Pi 3/4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)

- [Raspberry Pi OS (latest 64-bit version recommended)](https://www.raspberrypi.com/software/) 
 
- [SDL2](https://www.libsdl.org/)
 
- [SQLite3](https://www.sqlite.org/)
 
- [RF24](https://github.com/nRF24/RF24)

- C++17 compatible compiler

- [CMake](https://cmake.org/)

- [Git](https://git-scm.com/)
 

### Development:
  
- [GCC or Clang](https://gcc.gnu.org/) (for compilation)
  
- [GDB](https://www.gnu.org/software/gdb/) (for debugging)
  

## Initialization

1. Clone this repository 
       
       git clone https://github.com/ColePrather1/AI-ATC.git
       cd AI-ATC
       
2. Run initial setup script
       
       chmod +x install/initial.sh
       sudo ./install/initial.sh
            
3. Reboot to apply changes

       sudo reboot

## Compilation

1. Create & navigate to build directory

       cd AI-ATC
       mkdir build && cd build

2. Generate build files & compile

       cmake ..
       make

- To recompile, first clean the build directory:

       rm -rf *

## Execution

       ./bin/AI-ATC


## Troubleshooting

If you encounter any issues, please check the following:
- Ensure all dependencies are correctly installed
- Verify that your Raspberry Pi is running the latest OS version
- Check the console output for any error messages
- If SPIDEV fails to reserve GPIO access on occasional program execution, just try again

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
