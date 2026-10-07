#pragma once
#include <cstddef>
#include <utility>
#include <vector>

// Approach: a boundary index `store` marks the end of the "< pivot" prefix; scan once and swap each
//           smaller value into position `store`.
// Key insight: the prefix [0, store) is an invariant, so one pass and swaps are enough, with no extra array.
// Time: O(n)  Space: O(1)
// Brute force: copy into two new vectors (< pivot, >= pivot) and concatenate: O(n) time but O(n) space; or std::sort, O(n log n).
inline std::size_t partitionAround(std::vector<int>& nums, int pivot) {
    std::size_t store = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] < pivot) std::swap(nums[store++], nums[i]);
    }
    return store;
}
