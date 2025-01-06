#include <iostream>
//#include <queue>
//#include <mutex>
//#include <condition_variable>
#include <thread>
#include <chrono>
#include <atomic>
//#include <RF24/RF24.h>
//#include <SDL2/SDL.h>
//#include <sqlite3.h>

#include "ThreadSafeQueue.h"


ThreadSafeQueue data_queue;
std::atomic<bool> should_terminate(false);

// RF RX Thread
void rf_rx_thread(RF24& radio) {
    while (!should_terminate) {
        if (radio.available()) {
            DataPacket packet;
            packet.time = std::chrono::system_clock::now();
            radio.read(&packet, sizeof(packet));

            switch (packet.header) {
                case 'G': // GPS data
                    process_gps_data(packet);
                    break;
                case 'A': // Accelerometer data
                    process_accelerometer_data(packet);
                    break;
                case 'M': // Magnetometer data
                    process_magnetometer_data(packet);
                    break;
                case 'T': // Temperature data
                    process_temperature_data(packet);
                    break;
                case 'P': // Pressure data
                    process_pressure_data(packet);
                    break;
                default:
                    std::cerr << "Unknown packet header: " << packet.header << std::endl;
                    break;
            }

            data_queue.push(std::move(packet));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Example processing functions
void process_gps_data(const DataPacket& packet) {
    // Extract GPS data from packet.payload and process it
    std::cout << "Processing GPS data" << std::endl;
    std::cout << "Latitude: " << packet.lat << std::endl;
}

void process_accelerometer_data(const DataPacket& packet) {
    // Extract accelerometer data from packet.payload and process it
    std::cout << "Processing accelerometer data" << std::endl;
}

void process_magnetometer_data(const DataPacket& packet) {
    // Extract magnetometer data from packet.payload and process it
    std::cout << "Processing magnetometer data" << std::endl;
}

void process_temperature_data(const DataPacket& packet) {
    // Extract temperature data from packet.payload and process it
    std::cout << "Processing temperature data" << std::endl;
}

void process_pressure_data(const DataPacket& packet) {
    // Extract pressure data from packet.payload and process it
    std::cout << "Processing pressure data" << std::endl;
}

// SQL Logger Thread
void sql_logger_thread(sqlite3* db) {
    while (!should_terminate) {
        DataPacket packet;
        if (data_queue.pop(packet)) {
            // Log to SQL database
            // Use prepared statements for better performance
            // Example:
            // sqlite3_stmt* stmt;
            // sqlite3_prepare_v2(db, "INSERT INTO log_table (timestamp, rf_data) VALUES (?, ?)", -1, &stmt, NULL);
            // sqlite3_bind_int64(stmt, 1, std::chrono::system_clock::to_time_t(packet.timestamp));
            // sqlite3_bind_text(stmt, 2, packet.rf_data.c_str(), -1, SQLITE_STATIC);
            // sqlite3_step(stmt);
            // sqlite3_finalize(stmt);
        }
    }
}

// RF TX Thread
void rf_tx_thread(RF24& radio) {
    while (!should_terminate) {
        DataPacket packet;
        if (data_queue.pop(packet)) {
            // Transmit data via RF
            radio.write(packet.rf_data.c_str(), packet.rf_data.length());
        }
    }
}

// Controller Input Thread
void controller_input_thread(SDL_GameController* controller) {
    while (!should_terminate) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
                DataPacket packet;
                packet.timestamp = std::chrono::system_clock::now();
                // Process controller input and add to packet
                // Example:
                // packet.controller_data = process_controller_event(event);
                data_queue.push(std::move(packet));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    // Initialize RF24, SDL, and SQLite
    RF24 radio_rx(/* CE_PIN */, /* CSN_PIN */);
    RF24 radio_tx(/* CE_PIN */, /* CSN_PIN */);
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    SDL_GameController* controller = SDL_GameControllerOpen(0);
    sqlite3* db;
    sqlite3_open("log.db", &db);

    // Start threads
    std::thread rx_thread(rf_rx_thread, std::ref(radio_rx));
    std::thread sql_thread(sql_logger_thread, db);
    std::thread tx_thread(rf_tx_thread, std::ref(radio_tx));
    std::thread controller_thread(controller_input_thread, controller);
    std::thread ai_thread(input, data);

    // Main loop
    while (!should_terminate) {
        // Check for termination condition
        // Example: check for 'q' key press
        if (/* termination condition */) {
            should_terminate = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Join threads
    rx_thread.join();
    sql_thread.join();
    tx_thread.join();
    controller_thread.join();

    // Cleanup
    SDL_GameControllerClose(controller);
    SDL_Quit();
    sqlite3_close(db);

    return 0;
}


