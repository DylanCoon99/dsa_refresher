#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Approach: make events (time, +1 for start / -1 for end), sort so that at equal times ends (-1) come
//           first, then walk the events keeping a running count and its maximum.
// Key insight: with half-open intervals an end at time t frees its slot before a start at t needs one.
// Time: O(n log n)  Space: O(n)
// Brute force: for each start point count how many intervals contain it: O(n^2).
inline int maxOverlap(const std::vector<std::pair<int, int>>& intervals) {
    std::vector<std::pair<int, int>> ev;
    ev.reserve(intervals.size() * 2);
    for (const auto& iv : intervals) {
        ev.push_back({iv.first, +1});
        ev.push_back({iv.second, -1});
    }
    std::sort(ev.begin(), ev.end());  // (time, delta): -1 sorts before +1 at equal times
    int cur = 0, best = 0;
    for (const auto& e : ev) {
        cur += e.second;
        best = std::max(best, cur);
    }
    return best;
}
