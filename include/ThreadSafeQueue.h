#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
    int max_items = NULL;
    int size = 0;
public:

    ThreadSafeQueue() {}
    ThreadSafeQueue(int max_items) : max_items(max_items) {}

    bool full() {
        return size >= max_items;
    }


/*
TODO: Implement max items // Won't be exceeded as of now
*/
    void tryEnqueue(T value) {
        try {
            if (size >= max_items) {
                throw exception("Queue is full");
            }
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
            cond_.notify_one();
            //cond.notify_all();
            size++;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void enqueue(T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_.notify_one();
        //cond.notify_all();
        size++;
    }

    bool dequeue(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { return !queue_.empty(); });     // Retuens False if queue is empty
        item = std::move(queue_.front());
        queue_.pop();
        size--;
        return true;
    }


    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { return !queue_.empty(); });
        T item = std::move(queue_.front());
        queue_.pop();
        size--;
        return item;
    }

/*
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        T item = queue_.front();
        queue_.pop();
        return item;
    }
*/

/**
 * Checks if the queue is empty.
 * 
 * This method acquires a lock on the mutex to ensure thread-safety
 * while accessing the queue. It returns true if the queue is empty,
 * otherwise false.
 * 
 * @return True if the queue is empty, false otherwise.
 */

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

};



/*

class ThreadSafeQueue {
private:
    std::queue<DataPacket> queue;
    mutable std::mutex mutex;
    std::condition_variable cond;

public:
    void push(DataPacket value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(value));
        cond.notify_all();
    }

    bool pop(DataPacket& value) {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock, [this] { return !queue.empty(); });
        value = std::move(queue.front());
        queue.pop();
        return true;
    }
};


*/


