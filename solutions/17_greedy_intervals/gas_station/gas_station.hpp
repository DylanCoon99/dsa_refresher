#pragma once
#include <vector>

// Approach: one pass keeping the running tank from the current candidate start; when the tank goes
//           negative, no station in [start, i] can be the start, so restart at i + 1. If the total
//           gas is below the total cost the answer is -1.
// Key insight: failing at leg i from start s means every station between s and i fails too (they would
//              have begun with no more fuel than the run from s had), so skip them all at once.
// Time: O(n)  Space: O(1)
// Brute force: simulate the full circle from every station: O(n^2).
inline int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost) {
    const int n = static_cast<int>(gas.size());
    long long total = 0, tank = 0;
    int start = 0;
    for (int i = 0; i < n; ++i) {
        const int diff = gas[i] - cost[i];
        total += diff;
        tank += diff;
        if (tank < 0) {
            start = i + 1;
            tank = 0;
        }
    }
    return total >= 0 ? start : -1;
}
