#pragma once
#include <vector>

// nums is sorted ascending with distinct values.
// Return the index of target, or -1 if it is absent.
inline int search(const std::vector<int>& nums, int target) {
    // TODO: implement

    
    int idx;
    int l = 0;
    int r = nums.size() - 1;

    while (l <= r) {

        idx = l + (r - l) / 2;

        if (nums[idx] == target) {
            return idx;
        } else if (nums[idx] > target) {
            // search left half
            r = idx - 1;
        } else {
            // search right half
            l = idx + 1;
        }
    }

    return -1;
}
