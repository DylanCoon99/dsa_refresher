#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

// Approach: use each word's sorted letters as a canonical key in a hash map from key to group.
// Key insight: anagrams share a canonical form, so grouping is one hash-map pass instead of pairwise comparison.
// Time: O(n * L log L)  Space: O(n * L)
// Brute force: compare each word's sorted form with every existing group, O(n * groups * L).
inline std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (const std::string& w : strs) {
        std::string key = w;
        std::sort(key.begin(), key.end());
        groups[key].push_back(w);
    }
    std::vector<std::vector<std::string>> out;
    out.reserve(groups.size());
    for (auto& kv : groups) out.push_back(std::move(kv.second));
    return out;
}
