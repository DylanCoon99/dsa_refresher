#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: keep the window [left, right]; store each character's most recent index and, when the
//           new character was last seen inside the window, move left just past that index.
// Key insight: left only moves forward (use max), otherwise a stale index from before the window pulls it back.
// Time: O(n)  Space: O(alphabet)
// Brute force: check every substring for duplicates, O(n^2) substrings times O(n) to check (or O(n^2) with early exit).
inline int lengthOfLongestSubstring(const std::string& s) {
    std::vector<int> last(256, -1);
    int best = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        const unsigned char c = static_cast<unsigned char>(s[right]);
        left = std::max(left, last[c] + 1);
        last[c] = right;
        best = std::max(best, right - left + 1);
    }
    return best;
}
