#ifndef PAYLOAD_PARSER_H
#define PAYLOAD_PARSER_H
#pragma once

#include <cstdint>

#include <cstdint>
#include <array>

union Uint64ToUint8 {
    uint64_t u64;
    uint8_t u8[8];
};

std::array<uint8_t, 8> uint64ToUint8Array(uint64_t value) {
    Uint64ToUint8 converter;
    converter.u64 = value;
    return {
        converter.u8[7], converter.u8[6], converter.u8[5], converter.u8[4],
        converter.u8[3], converter.u8[2], converter.u8[1], converter.u8[0]
    };
}
/////////////////////////////////////

// Slower & Portable
std::array<uint8_t, 8> SLOWER_uint64ToUint8Array(uint64_t value) {
    return {
        static_cast<uint8_t>((value >> 56) & 0xFF),
        static_cast<uint8_t>((value >> 48) & 0xFF),
        static_cast<uint8_t>((value >> 40) & 0xFF),
        static_cast<uint8_t>((value >> 32) & 0xFF),
        static_cast<uint8_t>((value >> 24) & 0xFF),
        static_cast<uint8_t>((value >> 16) & 0xFF),
        static_cast<uint8_t>((value >> 8) & 0xFF),
        static_cast<uint8_t>(value & 0xFF)
    };
}


/*
uint64_t original = 0x0123456789ABCDEF;
auto bytes = uint64ToUint8Array(original);

for (int i = 0; i < 8; ++i) {
    printf("Byte %d: 0x%02X\n", i, bytes[i]);
}

*/

#endif // PAYLOAD_PARSER_H