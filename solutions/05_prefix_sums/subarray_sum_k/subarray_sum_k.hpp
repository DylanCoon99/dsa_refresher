#pragma once
#include <unordered_map>
#include <vector>

// Approach: scan once keeping the running sum; a hash map counts how often each earlier prefix sum
//           occurred, and each position adds count[running - k] to the answer.
// Key insight: a subarray sums to k exactly when two prefix sums differ by k, so counting becomes a lookup.
// Time: O(n)  Space: O(n)
// Brute force: for every start, extend the end and keep a running sum, O(n^2).
inline int subarraySum(const std::vector<int>& nums, int k) {
    std::unordered_map<long long, int> seen;
    seen[0] = 1;  // the empty prefix
    long long running = 0;
    int count = 0;
    for (int x : nums) {
        running += x;
        auto it = seen.find(running - k);
        if (it != seen.end()) count += it->second;
        ++seen[running];
    }
    return count;
}
