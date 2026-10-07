#pragma once
#include <algorithm>
#include <vector>

// Approach: f(i, w) = best value using items i..n-1 with capacity w: skip item i, or take it if it fits.
//           Memo caches (i, w). Tab keeps a 1-D array best[w] and, per item, iterates w downward so each
//           item is used at most once.
// Key insight: iterating capacity downward reads only values from before this item was considered.
// Time: O(n * capacity)  Space: O(n * capacity) memo, O(capacity) tab
// Brute force: enumerate all 2^n subsets.
namespace ks_detail {
inline int rec(const std::vector<int>& wt, const std::vector<int>& val, int i, int w,
               std::vector<std::vector<int>>& cache) {
    if (i == static_cast<int>(wt.size())) return 0;
    int& slot = cache[i][w];
    if (slot != -1) return slot;
    int best = rec(wt, val, i + 1, w, cache);
    if (wt[i] <= w) best = std::max(best, val[i] + rec(wt, val, i + 1, w - wt[i], cache));
    return slot = best;
}
}  // namespace ks_detail

inline int knapsackMemo(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    std::vector<std::vector<int>> cache(weights.size(), std::vector<int>(capacity + 1, -1));
    return ks_detail::rec(weights, values, 0, capacity, cache);
}

inline int knapsackTab(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    std::vector<int> best(capacity + 1, 0);
    for (std::size_t i = 0; i < weights.size(); ++i)
        for (int w = capacity; w >= weights[i]; --w) best[w] = std::max(best[w], best[w - weights[i]] + values[i]);
    return best[capacity];
}
