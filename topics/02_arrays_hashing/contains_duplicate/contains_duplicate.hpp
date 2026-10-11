#pragma once
#include <vector>
#include <unordered_set>

// Return true if any value appears at least twice in nums.
inline bool containsDuplicate(const std::vector<int>& nums) {
    // TODO: implement

    std::unordered_set<int> seen;

    for (auto n : nums) {
        if (seen.contains(n)) {
            return true;
        }
        seen.insert(n);
    }

    return false;
}
