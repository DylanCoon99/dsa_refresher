#pragma once
#include <string>

// Approach: for each of the 2n-1 centers, expand outwards while the ends match; each successful step is one palindrome.
// Key insight: the palindromes at a center are nested, so their number equals the radius reached.
// Time: O(n^2)  Space: O(1)
// Brute force: test every substring for being a palindrome, O(n^3).
inline int countSubstrings(const std::string& s) {
    const int n = static_cast<int>(s.size());
    int count = 0;
    for (int c = 0; c < 2 * n - 1; ++c) {
        int l = c / 2, r = l + c % 2;
        while (l >= 0 && r < n && s[l] == s[r]) {
            ++count;
            --l;
            ++r;
        }
    }
    return count;
}
