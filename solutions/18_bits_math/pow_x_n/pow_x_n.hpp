#pragma once

// Approach: square-and-multiply on |n|, using a long long exponent so INT_MIN can be negated;
//           for negative n, invert the base first.
// Key insight: x^n = (x^2)^(n/2), so the exponent halves each step; widen before negating.
// Time: O(log |n|)  Space: O(1)
// Brute force: multiply x by itself |n| times, O(|n|) (about 2*10^9 steps for INT_MAX).
inline double myPow(double x, int n) {
    long long e = n;  // -e is safe here even for INT_MIN
    if (e < 0) {
        x = 1.0 / x;
        e = -e;
    }
    double result = 1.0;
    while (e > 0) {
        if (e & 1) result *= x;
        x *= x;
        e >>= 1;
    }
    return result;
}
