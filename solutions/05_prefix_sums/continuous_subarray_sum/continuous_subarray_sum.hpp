#pragma once
#include <unordered_map>
#include <vector>

// Approach: track prefix sums mod k, storing the earliest index where each remainder appeared;
//           a repeat at distance >= 2 means the block between them sums to a multiple of k.
// Key insight: equal remainders of two prefix sums mean the block between them is divisible by k.
// Time: O(n)  Space: O(min(n, k))
// Brute force: try every start/end with length >= 2 and a running sum, O(n^2).
inline bool checkSubarraySum(const std::vector<int>& nums, int k) {
    std::unordered_map<long long, int> first;  // remainder -> earliest prefix length having it
    first[0] = 0;                              // the empty prefix
    long long running = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        running += nums[i];
        const long long rem = running % k;
        const int len = i + 1;  // prefix length
        auto it = first.find(rem);
        if (it == first.end())
            first[rem] = len;
        else if (len - it->second >= 2)
            return true;
    }
    return false;
}
