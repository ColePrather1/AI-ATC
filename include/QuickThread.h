#ifndef QUICK_THREAD_H
#define QUICK_THREAD_H
#pragma once
#include <thread>
#include <atomic>
#include <functional>
//#include <queue>

#include <memory>
#include <iostream>

//#include "ThreadSafeQueue.h"

class QuickThread {

private:
    std::function<bool()> setup;
    std::function<void()> loop;

    //std::atomic<bool> running;
    mutable std::atomic_bool running;
    std::thread thread;

    //std::unique_ptr<ThreadSafeQueue<void>> queue;

    //ThreadSafeQueue<void>* queue;
    //typename queue_type = NULL;
    //ThreadSafeQueue<queue_type>* queue;
    //ThreadSafeQueue<void>* queue;

    //void yield() { std::this_thread::yield(); }

    void run() {
        if (setup()) {
            while (running.load(std::memory_order_acquire)) {
                loop();
                //std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
        }
        else {
            std::cout << "Setup function failed" << std::endl;
        }
    }

    /*
    void run_old() {
        if (setup()) {
            while (running.load(std::memory_order_acquire)) {
                loop();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                //if (queue && !queue->empty()) {
                //    void* item = queue->pop();
                //    if (item) {
                //        // Process the item from the queue
                //        // You need to know the type to cast and use it correctly
                //        delete item; // Don't forget to delete the item after processing
                //    }
                //}

            }
        }
        else {
            std::cout << "Setup function failed" << std::endl;
        }
    }
    */


public:

/*
    QuickThread(std::function<bool()> setup_function, std::function<void()> loop_function)
        : setup(setup_function), loop(loop_function), running(false) {}
        
    void start() {
        if (!self.running) {
            self.running = true;
            self.thread = std::thread(&QuickThread::run, this);
        }
    }
*/

    QuickThread(std::function<bool()> setup_function, std::function<void()> loop_function)
        : setup(std::move(setup_function)), loop(std::move(loop_function)), running(false) {}

    ~QuickThread() {
        stop();
    }

    bool start() {
        if (!running.exchange(true)) {
            try {
                //thread = std::thread(&QuickThread::run, this);
                //thread = std::thread(&QuickThread::run, this);
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
        //self.running = false;
        running.store(false, std::memory_order_release);
        if (thread.joinable()) {
            thread.join();
            std::cout << "Thread joined" << std::endl;
        }
    }

    bool joinable() const {
        return thread.joinable();
    }


    /*
    template<typename T>
    void set_queue(ThreadSafeQueue<T>* q) {
        //queue.reset(q);
        queue.reset(static_cast<ThreadSafeQueue<void>*>(q));
    }

    bool has_queue() const {
        return queue != nullptr;
    }
    */




};


#endif // QUICK_THREAD_H