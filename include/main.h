#ifndef MAIN_H
#define MAIN_H
#pragma once

#include <thread>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "Session.h"


extern std::atomic<bool> quit_called{false};

class MainThread {
public:
    uint8_t data;
    std::thread keyboard_thread;
    std::atomic<bool> main_quit_flag{false};
    std::atomic<bool> main_finished{false};

    MainThread(uint8_t input) : data(input) {}

    ~MainThread() {
        main_quit_flag.store(true, std::memory_order_release);

        while (!main_finished.load(std::memory_order_relaxed)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        } // Wait for main thread to finish

        if (keyboard_thread.joinable()) {
            keyboard_thread.join();
        }
        if (!quit_called.load(std::memory_order_relaxed)) {
            quit();
        }
        return;
    }

    // Returns true if successful
    bool start() {
        keyboard_thread = std::thread(&MainThread::keyboardInputThread, this);
        return true;
    }

    void keyboardInputThread() {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        while (!main_quit_flag.load(std::memory_order_relaxed)
        && !Session::quit_flag.load(std::memory_order_relaxed)) {
            fd_set rfds;
            struct timeval tv;
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 10000;

            int retval = select(1, &rfds, NULL, NULL, &tv);
            if (retval == -1) {
                perror("select()");
            } else if (retval) {
                char ch = getchar();
                if (ch == 'q' || ch == 'Q') {
                    std::cout << "Keyboard quit triggered ..." << std::endl;
                    if (!quit_called.load(std::memory_order_acquire)) {
                        main_quit_flag.store(true, std::memory_order_release);
                        quit();
                    }
                    main_finished.store(true, std::memory_order_release);
                    break;
                }
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};


#endif // MAIN_H