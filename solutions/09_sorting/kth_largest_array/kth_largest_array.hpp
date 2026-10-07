#pragma once
#include <random>
#include <utility>
#include <vector>

// Approach: the k-th largest is index n - k in ascending order; select it with a random-pivot,
//           three-way-partition quickselect.
// Key insight: grouping keys equal to the pivot lets the search stop at once on all-equal input.
// Time: O(n) expected  Space: O(1) extra
// Brute force: sort descending and take index k - 1, O(n log n); a two-way partition is O(n^2)
//              on all-equal input.
inline int findKthLargest(std::vector<int>& nums, int k) {
    static std::mt19937 gen(24680);
    std::ptrdiff_t lo = 0, hi = static_cast<std::ptrdiff_t>(nums.size()) - 1;
    const std::ptrdiff_t target = static_cast<std::ptrdiff_t>(nums.size()) - k;
    while (true) {
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
