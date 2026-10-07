#pragma once
#include <vector>

// Approach: fill positions left to right; a used[] flag per input index marks what is already on the path.
// Key insight: choose an unused element, explore, then unmark it so the next sibling can reuse it.
// Time: O(n * n!)  Space: O(n) beyond the output
// Brute force: std::next_permutation over the sorted input (same asymptotic cost).
namespace permutations_detail {
inline void rec(const std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& path,
                std::vector<std::vector<int>>& out) {
    if (path.size() == nums.size()) {
        out.push_back(path);
        return;
    }
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        rec(nums, used, path, out);
        path.pop_back();
        used[i] = false;
    }
}
}  // namespace permutations_detail

inline std::vector<std::vector<int>> permute(const std::vector<int>& nums) {
    std::vector<std::vector<int>> out;
    std::vector<int> path;
    std::vector<bool> used(nums.size(), false);
    permutations_detail::rec(nums, used, path, out);
    return out;
}
