#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Approach: make events (position, +passengers at 'from' / -passengers at 'to'), sort by position with
//           drop-offs (negative deltas) first at equal positions, and keep a running total.
// Key insight: the load only changes at trip endpoints, so sweeping the 2n endpoints in order is enough;
//              positions up to 1e9 rule out a per-position array.
// Time: O(n log n)  Space: O(n)
// Brute force: for each trip start, add up the passengers of every trip covering it: O(n^2)
//              (or a difference array with one cell per position: O(max position), too big).
inline bool carPooling(const std::vector<std::vector<int>>& trips, int capacity) {
    std::vector<std::pair<int, int>> ev;
    ev.reserve(trips.size() * 2);
    for (const auto& t : trips) {
        ev.push_back({t[1], +t[0]});
        ev.push_back({t[2], -t[0]});
    }
    std::sort(ev.begin(), ev.end());  // (position, delta): negative deltas sort first at equal positions
    long long load = 0;
    for (const auto& e : ev) {
        load += e.second;
        if (load > capacity) return false;
    }
    return true;
}
