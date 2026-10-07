#pragma once
#include <cstdlib>
#include <numeric>
#include <vector>

// Approach: P - N = target and P + N = total, so count subsets with sum P = (total + target) / 2
//           (0 if that is negative, fractional, or above the total). 1-D counting knapsack, sums downward;
//           a zero doubles every entry, which is exactly "either sign".
// Key insight: signs turn into a subset-sum counting problem.
// Time: O(n * total)  Space: O(total)
// Brute force: try all 2^n sign assignments.
inline int findTargetSumWays(const std::vector<int>& nums, int target) {
    const int total = std::accumulate(nums.begin(), nums.end(), 0);
    if (std::abs(target) > total || (total + target) % 2 != 0) return 0;
    const int want = (total + target) / 2;
    std::vector<int> ways(want + 1, 0);
    ways[0] = 1;
    for (int x : nums)
        for (int s = want; s >= x; --s) ways[s] += ways[s - x];
    return ways[want];
}
