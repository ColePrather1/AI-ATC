cmake_minimum_required(VERSION 3.12)
project(RPI4_Multithreaded_Project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(SDL2 REQUIRED)

# Add RF24 library (assuming it's installed in a standard location)
find_library(RF24_LIBRARY rf24)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/RXThread.cpp
    src/TXThread.cpp
    src/SQLLoggerThread.cpp
    src/ComputationThread.cpp
    src/GameControllerThread.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Threads::Threads
    SQLite::SQLite3
    SDL2::SDL2
    ${RF24_LIBRARY}
)

# Enable OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

# Copy any necessary resources to the build directory
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Install the executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
