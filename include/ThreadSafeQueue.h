#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>

#include <iostream>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    int max_items = 0;
    int size = 0;
public:

    ThreadSafeQueue() {}
    ThreadSafeQueue(int max_items) : max_items(max_items) {}

    bool isFull() {
        return size >= max_items;
    }

    int getSize() {
        return size;
    }



    // TODO: Implement max items // Won't be exceeded as of now
    /*
    void tryEnqueue(T value) {
        try {
            if (size >= max_items) {
                //throw exception("Queue is full");
                std::exception e("Queue is full");
                throw e;
            }
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
            cond_.notify_one();
            //cond.notify_all();
            size++;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    */

    void enqueue(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_.notify_one();
        //cond.notify_all();
        ++size;
    }

    bool dequeue(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { return !queue_.empty(); });     // Retuens False if queue is empty
        item = std::move(queue_.front());
        queue_.pop();
        --size;
        return true;
    }

    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { return !queue_.empty(); });
        T item = std::move(queue_.front());
        queue_.pop();
        --size;
        return item;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    T front() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.front();
    }

};

#endif // THREAD_SAFE_QUEUE_H