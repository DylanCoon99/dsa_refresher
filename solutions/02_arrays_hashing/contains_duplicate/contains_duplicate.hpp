#pragma once
#include <unordered_set>
#include <vector>

// Approach: scan once, keeping a hash set of values seen so far; a failed insert means a duplicate.
// Key insight: "have I seen this value?" is an O(1) set lookup, so no pair scan is needed.
// Time: O(n) expected  Space: O(n)
// Brute force: compare every pair, O(n^2) time (or sort first: O(n log n)).
inline bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    seen.reserve(nums.size());
    for (int x : nums)
        if (!seen.insert(x).second) return true;
    return false;
}
