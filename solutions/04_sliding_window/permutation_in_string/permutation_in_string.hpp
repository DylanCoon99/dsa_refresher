#pragma once
#include <string>

// Approach: slide a window of length |s1| over s2, keeping 26 letter counts of the window minus those of s1;
//           track how many of the 26 differences are non-zero and answer true when none are.
// Key insight: sliding by one changes only two counters, so the "is this a permutation?" test is O(1) per step.
// Time: O(|s1| + |s2|)  Space: O(1)
// Brute force: sort (or count) each |s1|-long window of s2 and compare with s1, O(|s2| * |s1| log |s1|).
inline bool checkInclusion(const std::string& s1, const std::string& s2) {
    const int m = static_cast<int>(s1.size()), n = static_cast<int>(s2.size());
    if (m > n) return false;
    int diff[26] = {};
    int nonzero = 0;
    auto bump = [&](char c, int delta) {
        int& d = diff[c - 'a'];
        if (d == 0) ++nonzero;
        d += delta;
        if (d == 0) --nonzero;
    };
    for (int i = 0; i < m; ++i) {
        bump(s1[i], -1);
        bump(s2[i], +1);
    }
    if (nonzero == 0) return true;
    for (int i = m; i < n; ++i) {
        bump(s2[i], +1);
        bump(s2[i - m], -1);
        if (nonzero == 0) return true;
    }
    return false;
}
