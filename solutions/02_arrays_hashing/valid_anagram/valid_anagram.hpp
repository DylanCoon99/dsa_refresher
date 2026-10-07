#pragma once
#include <array>
#include <string>

// Approach: if the lengths differ, answer false; otherwise count letters of s up and of t down
//           and check that all 26 counters return to zero.
// Key insight: anagrams are exactly the strings with identical letter-count vectors.
// Time: O(n)  Space: O(1)
// Brute force: sort both strings and compare, O(n log n).
inline bool isAnagram(const std::string& s, const std::string& t) {
    if (s.size() != t.size()) return false;
    std::array<int, 26> cnt{};
    for (char c : s) ++cnt[c - 'a'];
    for (char c : t)
        if (--cnt[c - 'a'] < 0) return false;
    return true;
}
