#pragma once
#include <vector>

// Approach: mark composites by crossing out multiples of each prime p, starting at p*p.
// Key insight: any composite <= n has a prime factor <= sqrt(n), and smaller multiples of p
//              were already crossed out by smaller primes, so start at p*p.
// Time: O(n log log n)  Space: O(n)
// Brute force: trial-divide each number up to n, O(n sqrt(n)).
inline std::vector<int> primesUpTo(int n) {
    std::vector<int> primes;
    if (n < 2) return primes;
    std::vector<char> composite(static_cast<std::size_t>(n) + 1, 0);
    for (long long i = 2; i <= n; ++i) {
        if (composite[i]) continue;
        primes.push_back(static_cast<int>(i));
        for (long long j = i * i; j <= n; j += i) composite[j] = 1;
    }
    return primes;
}
