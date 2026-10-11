#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>

// Return the k most frequent values in nums, in any order. The answer is unique.
inline std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // TODO: implement

    // build a frequency map
    std::unordered_map<int, int> freq;
    for (auto n : nums) {
        freq[n] += 1;
    }

    // copy the map to a vector
    std::vector<std::pair<int, int>> vec(freq.begin(), freq.end());

    // use iterators to partially sort the map with a custom comparator
    std::partial_sort(vec.begin(), vec.begin() + k, vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    vec.resize(k);

    std::vector<int> result;

    for (auto pair : vec) {
        result.push_back(pair.first);
    }

    return result;
}
