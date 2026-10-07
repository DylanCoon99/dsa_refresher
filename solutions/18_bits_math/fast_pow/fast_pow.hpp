#pragma once

// Approach: square-and-multiply over the bits of exp, reducing mod after every product.
//           The base is normalised into [0, mod) first so negative bases work.
// Key insight: x^exp = (x^2)^(exp/2) (times x when exp is odd), so the exponent halves each step.
// Time: O(log exp)  Space: O(1)
// Brute force: multiply exp times, O(exp).
inline long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;  // 0 when mod == 1
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;  // both < mod <= 2e9, product < 4e18
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}
