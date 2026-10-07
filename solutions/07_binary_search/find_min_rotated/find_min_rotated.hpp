#pragma once
#include <vector>

// Approach: compare nums[mid] with nums[hi]; if smaller, the minimum is at mid or left of it,
//           otherwise it is strictly right of mid.
// Key insight: the last element tells which side of mid holds the "drop" in a rotated sorted array.
// Time: O(log n)  Space: O(1)
// Brute force: scan for the smallest element, O(n).
inline int findMin(const std::vector<int>& nums) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[hi]) hi = mid;
        else lo = mid + 1;
    }
    return nums[lo];
}
