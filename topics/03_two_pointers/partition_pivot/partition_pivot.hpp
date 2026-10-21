#pragma once
#include <cstddef>
#include <vector>

// Rearrange nums in place so that all values < pivot come first.
// Return how many values are < pivot. Order within each side is unspecified.
inline std::size_t partitionAround(std::vector<int>& nums, int pivot) {
    // TODO: implement
    if (nums.size() == 0) return 0;

    int i = 0;
    int j = nums.size() - 1;
    
    while (i <= j) {
        if (nums[i] < pivot) {
            ++i;
            continue;
        }
        if (nums[j] < pivot) {
            // swap i and j
            int temp = nums[j];
            nums[j] = nums[i];
            nums[i] = temp;
            --j;
            ++i;
        } else {
            --j;
        }
        
    }

    return i;
}
