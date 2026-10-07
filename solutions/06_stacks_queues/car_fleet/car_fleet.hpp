#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

// Approach: sort cars by position, nearest the target first. A car starts a new fleet exactly when
//           its own arrival time is strictly greater than the current front fleet's. Times are
//           compared as fractions with cross-multiplication in long long.
// Key insight: a faster car behind can only merge into the fleet ahead, so only the slowest
//              arrival time so far matters, which is a monotonic stack that never needs more than one entry.
// Time: O(n log n)  Space: O(n)
// Brute force: for each car, compare its arrival time with every car ahead of it, O(n^2).
inline int carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed) {
    const int n = static_cast<int>(position.size());
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) { return position[a] > position[b]; });
    int fleets = 0;
    long long frontDist = 0, frontSpeed = 1;  // arrival time of the front fleet = frontDist / frontSpeed
    for (int idx : order) {
        long long dist = target - position[idx], sp = speed[idx];
        // dist/sp > frontDist/frontSpeed  <=>  dist * frontSpeed > frontDist * sp
        if (fleets == 0 || dist * frontSpeed > frontDist * sp) {
            ++fleets;
            frontDist = dist;
            frontSpeed = sp;
        }
    }
    return fleets;
}
