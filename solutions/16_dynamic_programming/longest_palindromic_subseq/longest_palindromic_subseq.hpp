#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: L[i][j] = longest palindromic subsequence of s[i..j]; L[i][i] = 1; equal ends give 2 + L[i+1][j-1],
//           otherwise max(L[i+1][j], L[i][j-1]). Filled by increasing substring length.
// Key insight: either both ends are matched with each other, or at least one end is unused.
// Time: O(n^2)  Space: O(n^2)
// Brute force: test every subsequence for being a palindrome: O(2^n * n).
inline int longestPalindromeSubseq(const std::string& s) {
    const int n = static_cast<int>(s.size());
    if (n == 0) return 0;
    std::vector<std::vector<int>> L(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) L[i][i] = 1;
    for (int len = 2; len <= n; ++len)
        for (int i = 0; i + len - 1 < n; ++i) {
            const int j = i + len - 1;
            if (s[i] == s[j]) L[i][j] = (len == 2 ? 0 : L[i + 1][j - 1]) + 2;
            else L[i][j] = std::max(L[i + 1][j], L[i][j - 1]);
        }
    return L[0][n - 1];
}
