#pragma once
#include <algorithm>
#include <vector>

// Approach: scan once, tracking the lowest price seen so far; each day's best sale is price - lowest.
// Key insight: the best buy day for a given sell day is simply the minimum before it, so no pair needs checking.
// Time: O(n)  Space: O(1)
// Brute force: try every (buy, sell) pair with buy < sell, O(n^2).
inline int maxProfit(const std::vector<int>& prices) {
    int best = 0;
    int lowest = prices.empty() ? 0 : prices[0];
    for (int p : prices) {
        lowest = std::min(lowest, p);
        best = std::max(best, p - lowest);
    }
    return best;
}
