#pragma once
#include <vector>

// Approach: a read index scans the array; a write index marks the end of the unique prefix.
//           Copy an element only when it differs from the last kept one.
// Key insight: in a sorted array duplicates are adjacent, so comparing with the last kept value is enough.
// Time: O(n)  Space: O(1)
// Brute force: erase each duplicate from the vector as found (O(n^2) shifting), or copy into a set/new array (O(n) space).
inline int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int write = 1;
    for (int read = 1; read < static_cast<int>(nums.size()); ++read) {
        if (nums[read] != nums[write - 1]) nums[write++] = nums[read];
    }
    return write;
}
