#pragma once
#include <vector>
#include <unordered_set>

// Length of the longest run x, x+1, x+2, ... whose values all occur in nums. Empty input -> 0.
inline int longestConsecutive(const std::vector<int>& nums) {
    // TODO: implement
    if (nums.size() == 0) return 0;

    unordered_set<int> set(nums.begin(), nums.end());
    int longest_length = 0;

    // for every number check if n - 1 is in the set

    return -1;
}
