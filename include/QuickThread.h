#ifndef QUICK_THREAD_H
#define QUICK_THREAD_H
#pragma once
#include <thread>
#include <atomic>
#include <functional>
#include <memory>
#include <iostream>

class QuickThread {

private:
    std::function<bool()> setup;
    std::function<void()> loop;

    mutable std::atomic_bool running{false};
    std::thread thread;

    void run() {
        if (setup()) {
            running.store(true, std::memory_order_release);
            while (running.load(std::memory_order_acquire)) {
                loop();
            }
        }
        else {
            std::cout << "Setup function failed" << std::endl;
        }
    }

public:

    QuickThread(std::function<bool()> setup_function, std::function<void()> loop_function)
        : setup(std::move(setup_function)), loop(std::move(loop_function)) {}

    ~QuickThread() {
        stop();
    }

    bool start() {
        if (!running.load(std::memory_order_acquire)) {
            try {
                thread = std::thread(&QuickThread::run, this);
                return true;
            } catch (const std::system_error& e) {
                running.store(false);
                return false;
            }
        }
        return false;
    }

    void stop() {
        running.store(false, std::memory_order_release);
        if (thread.joinable()) {
            thread.join();
            std::cout << "Thread joined" << std::endl;
        }
    }

    bool joinable() const {
        return thread.joinable();
    }

};


#endif // QUICK_THREAD_H