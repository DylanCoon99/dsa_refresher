#pragma once
#include <cstdint>

// Approach: repeatedly clear the lowest set bit with n &= n - 1 and count the steps.
// Key insight: n & (n - 1) removes exactly one set bit, so the loop runs once per set bit.
// Time: O(popcount(n))  Space: O(1)
// Brute force: test each of the 32 bits one at a time, O(32).
inline int hammingWeight(std::uint32_t n) {
    int count = 0;
    while (n != 0) {
        n &= n - 1;
        ++count;
    }
    return count;
}
