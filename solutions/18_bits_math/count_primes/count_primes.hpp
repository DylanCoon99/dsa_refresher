#pragma once
#include <vector>

// Approach: Sieve of Eratosthenes over [0, n), counting the numbers never crossed out.
// Key insight: each prime crosses out its multiples starting at p*p; every composite < n is hit by a prime <= sqrt(n).
// Time: O(n log log n)  Space: O(n)
// Brute force: trial-divide every number below n, O(n sqrt(n)).
inline int countPrimes(int n) {
    if (n < 3) return 0;
    std::vector<char> composite(static_cast<std::size_t>(n), 0);
    int count = 0;
    for (long long i = 2; i < n; ++i) {
        if (composite[i]) continue;
        ++count;
        for (long long j = i * i; j < n; j += i) composite[j] = 1;
    }
    return count;
}
