#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: d[i][j] = distance between word1[0..i) and word2[0..j); d[i][0] = i, d[0][j] = j; equal last chars
//           copy d[i-1][j-1], else 1 + min(replace d[i-1][j-1], delete d[i-1][j], insert d[i][j-1]).
// Key insight: the last operation touches only the end of the prefixes, so it leads to one of three neighbours.
// Time: O(|a||b|)  Space: O(|a||b|)
// Brute force: the same three-way recursion without a cache: exponential.
inline int minDistance(const std::string& word1, const std::string& word2) {
    const std::size_t n = word1.size(), m = word2.size();
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1, 0));
    for (std::size_t i = 0; i <= n; ++i) d[i][0] = static_cast<int>(i);
    for (std::size_t j = 0; j <= m; ++j) d[0][j] = static_cast<int>(j);
    for (std::size_t i = 1; i <= n; ++i)
        for (std::size_t j = 1; j <= m; ++j) {
            if (word1[i - 1] == word2[j - 1]) d[i][j] = d[i - 1][j - 1];
            else d[i][j] = 1 + std::min({d[i - 1][j - 1], d[i - 1][j], d[i][j - 1]});
        }
    return d[n][m];
}
