#pragma once
#include <vector>

// Approach: at each step one of [lo, mid] / [mid, hi] is sorted; test whether target falls inside
//           the sorted half and keep that half, else keep the other.
// Key insight: a rotation leaves one half sorted at every split, which is enough to decide the side.
// Time: O(log n)  Space: O(1)
// Brute force: linear scan, O(n).
inline int search(const std::vector<int>& nums, int target) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[lo] <= nums[mid]) {  // left half [lo, mid] is sorted
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                       // right half [mid, hi] is sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
