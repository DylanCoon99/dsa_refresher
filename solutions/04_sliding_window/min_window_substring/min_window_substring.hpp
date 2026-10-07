#pragma once
#include <string>

// Approach: count what t needs; expand right, tracking how many needed characters are still missing;
//           when none are, shrink from the left as far as possible, recording the shortest window.
// Key insight: keep a single "missing" counter so that checking whether the window covers t is O(1), not O(alphabet).
// Time: O(|s| + |t|)  Space: O(alphabet)
// Brute force: for every substring of s test whether it covers t, O(|s|^2 * (|s| + |t|)) or O(|s|^2) with incremental counts.
inline std::string minWindow(const std::string& s, const std::string& t) {
    const int n = static_cast<int>(s.size());
    int need[128] = {};
    for (char c : t) ++need[static_cast<unsigned char>(c)];
    int missing = static_cast<int>(t.size());
    int bestLen = n + 1, bestStart = 0, left = 0;
    for (int right = 0; right < n; ++right) {
        if (need[static_cast<unsigned char>(s[right])]-- > 0) --missing;
        while (missing == 0) {
            if (right - left + 1 < bestLen) {
                bestLen = right - left + 1;
                bestStart = left;
            }
            if (++need[static_cast<unsigned char>(s[left])] > 0) ++missing;
            ++left;
        }
    }
    return bestLen > n ? "" : s.substr(bestStart, bestLen);
}
