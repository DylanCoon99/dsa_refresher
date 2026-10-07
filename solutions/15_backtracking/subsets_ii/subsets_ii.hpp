#pragma once
#include <algorithm>
#include <vector>

// Approach: sort, then backtrack with a start index; at each level skip a value equal to the one just tried.
// Key insight: after sorting, taking the second copy of a value without the first only re-creates a subset.
// Time: O(n * 2^n)  Space: O(n) beyond the output
// Brute force: all 2^n bitmasks, sort each subset, dedupe through a set.
namespace subsets_ii_detail {
inline void rec(const std::vector<int>& nums, int start, std::vector<int>& path,
                std::vector<std::vector<int>>& out) {
    out.push_back(path);
    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        if (i > start && nums[i] == nums[i - 1]) continue;  // same value already tried at this level
        path.push_back(nums[i]);
        rec(nums, i + 1, path, out);
        path.pop_back();
    }
}
}  // namespace subsets_ii_detail

inline std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> out;
    std::vector<int> path;
    subsets_ii_detail::rec(nums, 0, path, out);
    return out;
}
