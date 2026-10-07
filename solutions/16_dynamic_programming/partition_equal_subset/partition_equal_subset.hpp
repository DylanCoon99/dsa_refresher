#pragma once
#include <numeric>
#include <vector>

// Approach: if the total is odd the answer is no; otherwise subset-sum DP for total/2 with a 1-D
//           reachability array, iterating sums downward so each number is used once.
// Key insight: "two equal halves" is the same as "some subset sums to half the total".
// Time: O(n * sum)  Space: O(sum)
// Brute force: try all 2^n subsets.
inline bool canPartition(const std::vector<int>& nums) {
    const int total = std::accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0) return false;
    const int half = total / 2;
    std::vector<char> reach(half + 1, 0);
    reach[0] = 1;
    for (int x : nums)
        for (int s = half; s >= x; --s)
            if (reach[s - x]) reach[s] = 1;
    return reach[half];
}
