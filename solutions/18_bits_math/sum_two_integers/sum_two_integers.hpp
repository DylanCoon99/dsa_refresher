#pragma once

// Approach: half-adder loop: sum-without-carry is a ^ b, carry is (a & b) << 1; repeat until carry is 0.
//           The arithmetic is done on unsigned values so the shift is defined in every C++ standard.
// Key insight: XOR adds without carrying and AND finds the carries, so addition is XOR plus shifted AND, iterated.
// Time: O(32)  Space: O(1)
// Brute force: increment/decrement one operand |b| times (uses + / -, and is O(|b|)).
inline int getSum(int a, int b) {
    unsigned x = static_cast<unsigned>(a);
    unsigned y = static_cast<unsigned>(b);
    while (y != 0) {
        unsigned carry = (x & y) << 1;
        x ^= y;
        y = carry;
    }
    return static_cast<int>(x);  // value-preserving modulo 2^32 (defined in C++20)
}
