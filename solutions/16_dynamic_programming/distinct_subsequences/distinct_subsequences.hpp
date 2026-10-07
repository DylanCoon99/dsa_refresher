#pragma once
#include <string>
#include <vector>

// Approach: ways[j] = number of ways the first j chars of t appear in the prefix of s read so far; ways[0] = 1.
//           For each char of s, update j descending: if s[i] == t[j-1] then ways[j] += ways[j-1].
//           The row is unsigned long long: intermediate counts can overflow even 64 bits while the final answer
//           fits in int, and unsigned wraparound is defined and exact when the true answer fits.
// Key insight: each character of s either is skipped or becomes the last matched character of t's prefix.
// Time: O(|s||t|)  Space: O(|t|)
// Brute force: recurse over (i, j) without a cache: exponential.
inline int numDistinct(const std::string& s, const std::string& t) {
    std::vector<unsigned long long> ways(t.size() + 1, 0);
    ways[0] = 1;
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t j = t.size(); j >= 1; --j)
            if (s[i] == t[j - 1]) ways[j] += ways[j - 1];
    return static_cast<int>(ways[t.size()]);
}
