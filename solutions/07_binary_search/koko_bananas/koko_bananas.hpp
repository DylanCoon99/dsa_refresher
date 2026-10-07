#pragma once
#include <algorithm>
#include <vector>

// Approach: binary search on the speed k in [1, max pile]; feasible(k) = total hours <= h is monotone in k.
// Key insight: "smallest k such that ..." over a monotone predicate is binary search on the answer.
// Time: O(n log(max pile))  Space: O(1)
// Brute force: try k = 1, 2, 3, ... and recompute the hours each time, O(max pile * n).
inline int minEatingSpeed(const std::vector<int>& piles, int h) {
    int lo = 1, hi = *std::max_element(piles.begin(), piles.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        long long hours = 0;
        for (int p : piles) hours += (static_cast<long long>(p) + mid - 1) / mid;
        if (hours <= h) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
