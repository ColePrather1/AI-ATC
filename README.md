# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB


Requirements
Raspberry Pi 4 Model B 8GB
Raspberry Pi OS (latest version recommended)
SDL2
SQLite3
RF24 library
C++17 compatible compiler
CMake (version 3.12 or higher)
Git


# Requirements

- [Raspberry Pi 3/4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)

- [Raspberry Pi OS (latest version recommended)](https://www.raspberrypi.com/software/) 
 
- [SDL2](https://www.libsdl.org/)
 
- [SQLite3](https://www.sqlite.org/)
 
- [RF24](https://github.com/nRF24/RF24)

- [C++17 compatible compiler](...)

- [CMake](https://cmake.org/)

- [Git](https://git-scm.com/)
 

For development:
  
- [GCC or Clang](https://gcc.gnu.org/) (for compilation)
  
- [GDB](https://www.gnu.org/software/gdb/) (for debugging)
  
- [mypy](https://mypy-lang.org/) (for type check)
  
- [sphinx](https://www.sphinx-doc.org/) (for document generation)
  
- [pycodestyle](https://pypi.org/project/pycodestyle/) (for code style check)


# How to use

       1. Clone this repository 

              ```terminal
              git clone https://github.com/ColePrather1/AI-ATC.git
              ```

       2. Run inital setup script

              ```terminal
              cd AI-ATC
              chmod +x install/initial.sh
              sudo ./install/initial.sh
              ```            

       3. Reboot to apply changes

              ```terminal
              sudo reboot
              ```

       4. Compilation

              ```terminal
              cd AI-ATC
              mkdir build && cd build
              cmake ..
              make
              ```

              To recompile, first clean the build directory:

              ```terminal
              rm -rf *
              ```

       5. Execution

              ```terminal
              ./bin/AI-ATC
              ```

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
