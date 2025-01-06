

class AtomicPointerArray {
private:
    std::array<float*, 5> data;
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void store(const std::array<float*, 5>& values, std::memory_order order) {
        while (flag.test_and_set(std::memory_order_acquire));
        data = values;
        flag.clear(order);
    }

    std::array<float*, 5> load(std::memory_order order) const {
        while (flag.test_and_set(std::memory_order_acquire));
        auto result = data;
        flag.clear(order);
        return result;
    }
};
