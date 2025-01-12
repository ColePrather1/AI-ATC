#ifndef BITMASK_H
#define BITMASK_H

#pragma once

/*

#include <cstdint>
#include <stdexcept>

class Bitmask {
private:
    std::uint16_t mask;

    class BitProxy {
    private:
        std::uint16_t& mask;
        int position;

    public:
        BitProxy(std::uint16_t& m, int pos) : mask(m), position(pos) {}

        operator bool() const {
            return (mask & (1ULL << position)) != 0;
        }

        BitProxy& operator=(bool value) {
            if (value) {
                mask |= (1ULL << position);
            } else {
                mask &= ~(1ULL << position);
            }
            return *this;
        }
    };

public:
    Bitmask() : mask(0) { }
    Bitmask(std::uint16_t m) : mask(m) { }

    void set(int position) {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        mask |= (1ULL << position);
    }

    void clear(int position) {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        mask &= ~(1ULL << position);
    }

    bool test(int position) const {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        return (mask & (1ULL << position)) != 0;
    }

    void toggle(int position) {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        mask ^= (1ULL << position);
    }

    BitProxy operator[](int position) {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        return BitProxy(mask, position);
    }

    bool operator[](int position) const {
        if (position < 0 || position >= 16) {
            throw std::out_of_range("Bit position out of range");
        }
        return (mask & (1ULL << position)) != 0;
    }

    bool operator==(const Bitmask& other) const {
        return mask == other.mask;
    }

    bool operator!=(const Bitmask& other) const {
        return !(*this == other);
    }

};



class Bitmask8 {
private:
    std::uint8_t mask;

    class BitProxy {
    private:
        std::uint8_t& mask;
        int position;

    public:
        BitProxy(std::uint8_t& m, int pos) : mask(m), position(pos) {}

        operator bool() const {
            return (mask & (1ULL << position)) != 0;
        }

        BitProxy& operator=(bool value) {
            if (value) {
                mask |= (1ULL << position);
            } else {
                mask &= ~(1ULL << position);
            }
            return *this;
        }
    };

public:
    Bitmask() : mask(0) { }
    Bitmask(std::uint8_t m) : mask(m) { }

    void set(int position) {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        mask |= (1ULL << position);
    }

    void clear(int position) {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        mask &= ~(1ULL << position);
    }

    bool test(int position) const {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        return (mask & (1ULL << position)) != 0;
    }

    void toggle(int position) {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        mask ^= (1ULL << position);
    }

    BitProxy operator[](int position) {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        return BitProxy(mask, position);
    }

    bool operator[](int position) const {
        if (position < 0 || position >= 8) {
            throw std::out_of_range("Bit position out of range");
        }
        return (mask & (1ULL << position)) != 0;
    }

    bool operator==(const Bitmask& other) const {
        return mask == other.mask;
    }

    bool operator!=(const Bitmask& other) const {
        return !(*this == other);
    }

};
*/


/*
int main() {
    Bitmask bm;

    // Setting bits
    bm[0] = true;  // Set bit 0
    bm[3] = true;  // Set bit 3

    // Reading bits
    bool bit0 = bm[0];  // true
    bool bit1 = bm[1];  // false
    bool bit3 = bm[3];  // true

    // Toggling bits
    bm[0] = !bm[0];  // Toggle bit 0

    // Using existing methods
    bm.set(5);
    bm.clear(3);
    bm.toggle(2);

    return 0;
}
*/



#endif