#pragma once
#include <algorithm>
#include <vector>

// Approach: best[i] = max(best[i-1], best[i-2] + nums[i]) kept in two variables.
// Key insight: taking house i forbids i-1, so it combines with the best of the first i-1 houses minus one.
// Time: O(n)  Space: O(1)
// Brute force: try every subset of non-adjacent houses: O(2^n).
inline int rob(const std::vector<int>& nums) {
    int skip = 0, take = 0;  // best total for houses so far: without / with the previous house chosen
    for (int x : nums) {
        int newTake = skip + x;
        skip = std::max(skip, take);
        take = newTake;
    }
    return std::max(skip, take);
}
