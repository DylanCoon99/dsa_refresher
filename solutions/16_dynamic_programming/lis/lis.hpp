#pragma once
#include <algorithm>
#include <vector>

// Approach: tail[k] = smallest possible last value of a strictly increasing subsequence of length k+1.
//           tail stays sorted, so each number replaces the first entry >= it (lower_bound) or is appended.
// Key insight: for a given length, a smaller ending value is never worse, so only that one needs remembering.
// Time: O(n log n)  Space: O(n)
// Brute force: len[i] = 1 + max len[j] over j < i with nums[j] < nums[i]: O(n^2).
inline int lengthOfLIS(const std::vector<int>& nums) {
    std::vector<int> tail;
    for (int x : nums) {
        auto it = std::lower_bound(tail.begin(), tail.end(), x);  // lower_bound: equal values replace, not extend
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return static_cast<int>(tail.size());
}
