#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#pragma once
#include <vector>
#include <cstdint>
#include <cstring>

template<typename T>
std::vector<uint64_t> serialize(const T& obj) {
    static_assert(sizeof(T) % sizeof(uint64_t) == 0, "Size of T must be a multiple of sizeof(uint64_t)");
    
    std::vector<uint64_t> result(sizeof(T) / sizeof(uint64_t));
    std::memcpy(result.data(), &obj, sizeof(T));
    
    return result;
}

template<typename T>
T deserialize(const std::vector<uint64_t>& data) {
    static_assert(sizeof(T) % sizeof(uint64_t) == 0, "Size of T must be a multiple of sizeof(uint64_t)");
    
    T result;
    std::memcpy(&result, data.data(), sizeof(T));
    
    return result;
}



#endif // SERIALIZATION_H