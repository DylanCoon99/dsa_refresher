#pragma once
#include <utility>
#include <vector>

// Approach: Dutch national flag. Keep 0s in [0, lo), 1s in [lo, i), unknown in [i, hi], 2s after hi.
// Key insight: a value swapped in from the back is unexamined, so i must not advance past it.
// Time: O(n), one pass  Space: O(1)
// Brute force: count each color then rewrite (two passes), or any O(n log n) sort.
inline void sortColors(std::vector<int>& nums) {
    int lo = 0, i = 0, hi = static_cast<int>(nums.size()) - 1;
    while (i <= hi) {
        if (nums[i] == 0) std::swap(nums[lo++], nums[i++]);
        else if (nums[i] == 2) std::swap(nums[i], nums[hi--]);
        else ++i;
    }
}
