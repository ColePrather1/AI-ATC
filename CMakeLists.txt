cmake_minimum_required(VERSION 3.12)
project(AI-ATC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimize for Raspberry Pi 4
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a72 -mtune=cortex-a72")

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SQLite3 REQUIRED)
find_library(RF24_LIBRARY rf24 HINTS /usr/local/lib)

# Define source files
set(SOURCES
    src/main.cpp
    #src/SQL.cpp
    src/FlightDatabase.cpp
    src/GameController.cpp
    src/Logging.cpp
    src/myTime.cpp
    #src/Session.cpp
    #src/CommonTools.cpp
    src/atc.cpp
    #src/RadioTx.cpp
)

# Define packet source files
file(GLOB PACKET_SOURCES src/packets/*.cpp)

# Define control mode source files
file(GLOB CONTROL_MODE_SOURCES src/ControlModes/*.cpp)

# Define thread source files
file(GLOB THREAD_SOURCES src/threads/*.cpp)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${PACKET_SOURCES}
    ${CONTROL_MODE_SOURCES}
    ${THREAD_SOURCES}
)

# Set include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SQLite3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${RF24_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SQLite::SQLite3
    ${RF24_LIBRARY}
    SDL2::SDL2
    pthread
)

# Set output directory
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
