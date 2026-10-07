#pragma once
#include <vector>

// Approach: closed range [lo, hi]; compare with the middle and discard the half that cannot hold target.
// Key insight: sortedness lets one comparison eliminate half the candidates.
// Time: O(log n)  Space: O(1)
// Brute force: scan every element, O(n) per query.
inline int search(const std::vector<int>& nums, int target) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
