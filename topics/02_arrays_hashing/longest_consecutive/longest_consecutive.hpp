#pragma once
#include <vector>
#include <set>

// Length of the longest run x, x+1, x+2, ... whose values all occur in nums. Empty input -> 0.
inline int longestConsecutive(const std::vector<int>& nums) {
    // TODO: implement
    if (nums.size() == 0) return 0;

    // create a set from nums; the set should be sorted (ascending)
    std::set<long long> set(nums.begin(), nums.end());

    int longest_run = 0;

    // any number n where n - 1 isn't in the set will be at the start of a run

    for (long long num : set) {
        int count = 0;

        if (!set.contains(num - 1)) {
            // this is the start of a run
            ++count;
            long long current_num = num;
            while (set.contains(current_num + 1)) {
                ++count;
                ++current_num;
            }
            if (count > longest_run) {
                longest_run = count;
            }
        }
    }
    
    return longest_run;
}
