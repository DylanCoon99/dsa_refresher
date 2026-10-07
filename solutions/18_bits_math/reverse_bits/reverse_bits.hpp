#pragma once
#include <cstdint>

// Approach: for each of the 32 positions, shift the result left and append the low bit of n, then shift n right.
// Key insight: peeling bits off the bottom of n and pushing them onto the bottom of the result reverses their order.
// Time: O(32)  Space: O(1)
// Brute force: build a 32-character binary string, reverse it, parse it back, O(32).
inline std::uint32_t reverseBits(std::uint32_t n) {
    std::uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result = (result << 1) | (n & 1u);
        n >>= 1;
    }
    return result;
}
