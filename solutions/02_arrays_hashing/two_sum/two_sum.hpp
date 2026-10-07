#pragma once
#include <unordered_map>
#include <vector>

// Approach: one pass; a hash map from value to its earliest index answers
//           "have I already seen target - x?" in O(1).
// Key insight: remembering the values you've passed turns the inner search loop into a lookup.
// Time: O(n) average  Space: O(n)
// Brute force: check every pair i < j, O(n^2) time.
inline std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<long long, int> seen;
    for (int j = 0; j < static_cast<int>(nums.size()); ++j) {
        auto it = seen.find(static_cast<long long>(target) - nums[j]);
        if (it != seen.end()) return {it->second, j};
        seen.emplace(nums[j], j);  // emplace keeps the earliest index for duplicates
    }
    return {};
}
