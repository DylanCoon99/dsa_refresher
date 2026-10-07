#pragma once
#include <algorithm>
#include <vector>

// Approach: the first and last houses can't both be taken, so the answer is the better of the
//           straight-street answer on [0, n-2] and on [1, n-1]; n = 1 is handled separately.
// Key insight: breaking the circle by forbidding one of the two conflicting houses leaves two line problems.
// Time: O(n)  Space: O(1)
// Brute force: try every subset with the circular adjacency check: O(2^n).
namespace hr2_detail {
inline int line(const std::vector<int>& v, std::size_t lo, std::size_t hi) {  // houses [lo, hi)
    int skip = 0, take = 0;
    for (std::size_t i = lo; i < hi; ++i) {
        int newTake = skip + v[i];
        skip = std::max(skip, take);
        take = newTake;
    }
    return std::max(skip, take);
}
}  // namespace hr2_detail

inline int rob(const std::vector<int>& nums) {
    const std::size_t n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return std::max(hr2_detail::line(nums, 0, n - 1), hr2_detail::line(nums, 1, n));
}
