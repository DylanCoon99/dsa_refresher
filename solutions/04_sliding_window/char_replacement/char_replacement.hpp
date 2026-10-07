#pragma once
#include <algorithm>
#include <string>

// Approach: variable window with 26 counters; the window is valid while length - maxCount <= k, else shrink by one.
// Key insight: maxCount may be stale (never decreased) because the answer only grows when a new, truly larger count appears.
// Time: O(n)  Space: O(1)
// Brute force: for every substring count letters and test length - max <= k, O(n^2 * 26).
inline int characterReplacement(const std::string& s, int k) {
    int count[26] = {};
    int best = 0, maxCount = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        maxCount = std::max(maxCount, ++count[s[right] - 'A']);
        if (right - left + 1 - maxCount > k) {
            --count[s[left] - 'A'];
            ++left;
        }
        best = std::max(best, right - left + 1);
    }
    return best;
}
