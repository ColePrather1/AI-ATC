

#include <bitset>
#include <cstring>
#include <type_traits>

template<typename T, std::size_t SIZE = (sizeof(T) * CHAR_BIT)>
std::bitset<SIZE> as_bits(const T& var) noexcept {
    if constexpr (std::is_trivially_copyable_v<T>) {
        std::bitset<SIZE> bits;
        std::memcpy(&bits, &var, sizeof(T));
        return bits;
    } else {
        // For non-trivially copyable types, this is not safe and should not be used
        static_assert(std::is_trivially_copyable_v<T>, "Type must be trivially copyable");
        return std::bitset<SIZE>(); // Return empty bitset if assertion fails
    }
}

