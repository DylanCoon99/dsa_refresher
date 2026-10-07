#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>

// Approach: grow the window by one character on the right; while the predicate rejects it, shrink
//           from the left. Record the window length after each step.
// Key insight: with a monotone predicate, an invalid window can never be fixed by growing it, so the
//              left end only ever moves forward and each character is added and removed once.
// Time: O(n * cost of is_valid)  Space: O(alphabet)
// Brute force: test every substring from scratch, O(n^2) windows each costing O(n) to count.
template <typename Valid>
int longestValidWindow(const std::string& s, Valid is_valid) {
    std::unordered_map<char, int> freq;
    int best = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        ++freq[s[right]];
        while (!is_valid(freq, right - left + 1)) {
            --freq[s[left]];
            ++left;
        }
        best = std::max(best, right - left + 1);
    }
    return best;
}
