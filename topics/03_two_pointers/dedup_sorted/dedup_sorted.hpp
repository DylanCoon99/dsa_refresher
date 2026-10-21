#pragma once
#include <vector>

// Given a sorted vector, move the distinct values (in order) to the front, in place.
// Return k, the number of distinct values. Entries after position k are unspecified.
inline int removeDuplicates(std::vector<int>& nums) {
    // TODO: implement
    if (nums.size() == 0) return 0;

    int i = 0;
    int j = 0;

    int result = 1;

    while (j < nums.size()) {
        // i points to the front (next place to insert a duplicate)
        // j points to the current num (the num we check if it is a duplicate)

        if (nums[i] == nums[j]) {
            ++j;
            continue;
        } else {
            ++i;
            // swap
            int temp = nums[j];
            nums[j] = nums[i];
            nums[i] = temp;
            ++result;
            ++j;
        }

    }


    return result;
}
