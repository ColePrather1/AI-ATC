cmake_minimum_required(VERSION 3.12)
project(AI_ATC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SQLite3 REQUIRED)

# Include directories
#include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)


# Add RF24 library
add_library(RF24 STATIC IMPORTED)
set_target_properties(RF24 PROPERTIES IMPORTED_LOCATION "/usr/local/lib/librf24.so")

# Add executable
add_executable(atc_system
    src/main.cpp
    src/atc.cpp
)

# Link libraries
target_link_libraries(atc_system
    SDL2::SDL2
    SQLite3::SQLite3
    RF24
)
