#pragma once
#include <algorithm>
#include <vector>

// Approach: sort by end; keep an interval if it starts at or after the end of the last kept one,
//           otherwise count it as removed.
// Key insight: among intervals competing for the same slot, the one that ends earliest leaves the most
//              room, and swapping it in for any other choice never reduces the kept count (exchange argument).
// Time: O(n log n)  Space: O(1) extra
// Brute force: sort by start and run an O(n^2) longest-compatible-chain DP (or try every subset: O(2^n)).
inline int eraseOverlapIntervals(std::vector<std::vector<int>> intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) { return a[1] < b[1]; });
    int removed = 0;
    long long lastEnd = -1;  // starts are >= 0, so -1 accepts the first interval
    for (const auto& iv : intervals) {
        if (iv[0] >= lastEnd)
            lastEnd = iv[1];
        else
            ++removed;
    }
    return removed;
}
