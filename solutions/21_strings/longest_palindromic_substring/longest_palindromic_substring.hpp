#pragma once
#include <string>

// Approach: for each of the 2n-1 centers (a character or a gap), expand outwards while the two ends match; keep the best.
// Key insight: a palindrome is fixed by its center and radius, and a bigger palindrome contains a smaller one around the same center.
// Time: O(n^2)  Space: O(1)
// Brute force: test every substring for being a palindrome, O(n^3).
inline std::string longestPalindrome(const std::string& s) {
    const int n = static_cast<int>(s.size());
    int bestStart = 0, bestLen = 0;
    for (int c = 0; c < 2 * n - 1; ++c) {
        int l = c / 2, r = l + c % 2;
        while (l >= 0 && r < n && s[l] == s[r]) {
            --l;
            ++r;
        }
        if (r - l - 1 > bestLen) {
            bestLen = r - l - 1;
            bestStart = l + 1;
        }
    }
    return s.substr(bestStart, bestLen);
}
