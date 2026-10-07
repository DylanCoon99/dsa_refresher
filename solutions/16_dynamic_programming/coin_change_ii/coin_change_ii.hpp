#pragma once
#include <vector>

// Approach: for each coin in turn, ways[a] += ways[a - coin] over a ascending (unbounded knapsack count).
//           The table is unsigned long long: intermediate counts can exceed even 32 bits while the final answer
//           fits, and unsigned wraparound is defined and exact when the true answer fits.
// Key insight: coins in the outer loop fixes an order on denominations, so each combination is counted once.
// Time: O(amount * coins)  Space: O(amount)
// Brute force: recurse over (coin index, remaining amount) without caching: exponential.
inline int change(int amount, const std::vector<int>& coins) {
    std::vector<unsigned long long> ways(amount + 1, 0);
    ways[0] = 1;
    for (int c : coins)
        for (int a = c; a <= amount; ++a) ways[a] += ways[a - c];
    return static_cast<int>(ways[amount]);
}
