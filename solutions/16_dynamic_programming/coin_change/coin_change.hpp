#pragma once
#include <algorithm>
#include <vector>

// Approach: best[a] = 1 + min over coins c <= a of best[a - c]; best[0] = 0; unreachable = INF.
//           Memo fills best lazily from the top (a = amount down to 0); Tab fills a = 0..amount.
// Key insight: the last coin used leaves an independent smaller problem, so "fewest coins for a"
//              only depends on "fewest coins for a - c" (optimal substructure).
// Time: O(amount * coins)  Space: O(amount)
// Brute force: try every coin at every step without caching: exponential in amount.
namespace cc_detail {
constexpr int kInf = 1 << 29;  // large enough to lose every min, small enough that +1 never overflows

inline int rec(const std::vector<int>& coins, int a, std::vector<int>& cache) {
    if (a == 0) return 0;
    int& slot = cache[a];
    if (slot != -2) return slot;  // -2 = not computed yet
    int best = kInf;
    for (int c : coins)
        if (c <= a) best = std::min(best, rec(coins, a - c, cache) + 1);
    return slot = best;
}
}  // namespace cc_detail

inline int coinChangeMemo(const std::vector<int>& coins, int amount) {
    std::vector<int> cache(amount + 1, -2);
    int r = cc_detail::rec(coins, amount, cache);
    return r >= cc_detail::kInf ? -1 : r;
}

inline int coinChangeTab(const std::vector<int>& coins, int amount) {
    std::vector<int> best(amount + 1, cc_detail::kInf);
    best[0] = 0;
    for (int a = 1; a <= amount; ++a)
        for (int c : coins)
            if (c <= a) best[a] = std::min(best[a], best[a - c] + 1);
    return best[amount] >= cc_detail::kInf ? -1 : best[amount];
}
