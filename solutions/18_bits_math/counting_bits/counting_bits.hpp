#pragma once
#include <vector>

// Approach: DP on earlier answers: ans[i] = ans[i >> 1] + (i & 1).
// Key insight: i is i/2 with one extra low bit, and i/2 < i has already been counted.
// Time: O(n)  Space: O(n) for the output
// Brute force: count the bits of every number separately, O(n log n).
inline std::vector<int> countBits(int n) {
    std::vector<int> ans(static_cast<std::size_t>(n) + 1, 0);
    for (int i = 1; i <= n; ++i) ans[i] = ans[i >> 1] + (i & 1);
    return ans;
}
