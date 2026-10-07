#pragma once
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

// Approach: random pivot, three-way partition into < / == / > groups; keep only the group that
//           contains index k, and stop as soon as k lands in the "equal" group.
// Key insight: handling the equal keys as their own group makes all-equal input finish in one pass.
// Time: O(n) expected  Space: O(1) extra
// Brute force: sort and return nums[k], O(n log n); a two-way partition degrades to O(n^2) on
//              all-equal input.
inline int quickselect(std::vector<int>& nums, std::size_t k) {
    static std::mt19937 gen(987654321);
    std::ptrdiff_t lo = 0, hi = static_cast<std::ptrdiff_t>(nums.size()) - 1;
    const std::ptrdiff_t target = static_cast<std::ptrdiff_t>(k);
    while (true) {  // invariant: the answer lies in nums[lo..hi] at sorted position target
        if (lo == hi) return nums[static_cast<std::size_t>(lo)];
        int pivot = nums[static_cast<std::size_t>(
            lo + static_cast<std::ptrdiff_t>(gen() % static_cast<unsigned>(hi - lo + 1)))];
        std::ptrdiff_t lt = lo, i = lo, gt = hi;
        while (i <= gt) {
            if (nums[static_cast<std::size_t>(i)] < pivot) {
                std::swap(nums[static_cast<std::size_t>(lt++)], nums[static_cast<std::size_t>(i++)]);
            } else if (nums[static_cast<std::size_t>(i)] > pivot) {
                std::swap(nums[static_cast<std::size_t>(i)], nums[static_cast<std::size_t>(gt--)]);
            } else {
                ++i;
            }
        }
        if (target < lt) hi = lt - 1;
        else if (target > gt) lo = gt + 1;
        else return pivot;
    }
}
