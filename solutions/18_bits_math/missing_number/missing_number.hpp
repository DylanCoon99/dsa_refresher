#pragma once
#include <vector>

// Approach: XOR every index 0..n with every value; each present number cancels, the missing one stays.
// Key insight: x ^ x == 0, so XOR over 0..n and over nums leaves only the number that is in the
//              range but not in the list.
// Time: O(n)  Space: O(1)
// Brute force: for each v in 0..n scan nums for v, O(n^2) (sorting or a hash set gives O(n log n) / O(n)).
inline int missingNumber(const std::vector<int>& nums) {
    int result = static_cast<int>(nums.size());
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) result ^= i ^ nums[i];
    return result;
}
