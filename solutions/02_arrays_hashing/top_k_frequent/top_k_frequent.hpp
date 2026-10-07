#pragma once
#include <unordered_map>
#include <vector>

// Approach: count occurrences in a hash map, bucket the values by count (counts are in 1..n),
//           then read buckets from the highest count down until k values are collected.
// Key insight: a count can't exceed n, so bucket sort by frequency replaces the O(n log n) sort.
// Time: O(n)  Space: O(n)
// Brute force: sort the distinct values by count, O(n log n).
inline std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> cnt;
    for (int x : nums) ++cnt[x];
    std::vector<std::vector<int>> bucket(nums.size() + 1);
    for (auto& kv : cnt) bucket[kv.second].push_back(kv.first);
    std::vector<int> out;
    for (std::size_t c = bucket.size(); c-- > 0 && static_cast<int>(out.size()) < k;)
        for (int v : bucket[c])
            if (static_cast<int>(out.size()) < k) out.push_back(v);
    return out;
}
