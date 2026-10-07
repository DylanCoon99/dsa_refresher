#pragma once
#include <vector>

// Approach: backtrack with a start index; record the path at every node, then extend with later elements.
// Key insight: recording at every node (not only at leaves) and only moving forward yields each subset once.
// Time: O(n * 2^n)  Space: O(n) beyond the output
// Brute force: iterate all 2^n bitmasks (same asymptotic cost).
namespace subsets_detail {
inline void rec(const std::vector<int>& nums, int start, std::vector<int>& path,
                std::vector<std::vector<int>>& out) {
    out.push_back(path);
    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        path.push_back(nums[i]);
        rec(nums, i + 1, path, out);
        path.pop_back();
    }
}
}  // namespace subsets_detail

inline std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    std::vector<std::vector<int>> out;
    std::vector<int> path;
    subsets_detail::rec(nums, 0, path, out);
    return out;
}
