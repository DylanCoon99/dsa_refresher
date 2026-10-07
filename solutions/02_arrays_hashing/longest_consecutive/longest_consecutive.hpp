#pragma once
#include <algorithm>
#include <unordered_set>
#include <vector>

// Approach: put all values in a hash set; only from a value x with x-1 absent (the start of a run)
//           walk upward through x+1, x+2, ... counting the run.
// Key insight: skipping non-starts means each element is visited at most twice, so the total work is O(n).
// Time: O(n) expected  Space: O(n)
// Brute force: from every element walk upward with set lookups (O(n^2)), or sort and scan (O(n log n)).
inline int longestConsecutive(const std::vector<int>& nums) {
    std::unordered_set<long long> set(nums.begin(), nums.end());  // long long: x +- 1 can't overflow
    int best = 0;
    for (long long x : set) {
        if (set.count(x - 1)) continue;
        int len = 1;
        while (set.count(x + len)) ++len;
        best = std::max(best, len);
    }
    return best;
}
