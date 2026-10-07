#pragma once
#include <string>
#include <vector>

// Approach: pi[i] extends the border of pi[i-1] when the next character matches, otherwise falls back along
//           shorter borders (pi[k-1]); the matcher runs the same loop over the text with pattern as the table.
// Key insight: each fallback strictly shrinks the current border, and the border grows by at most 1 per character, so the total work is amortised O(n).
// Time: O(n + m)  Space: O(m)
// Brute force: try the pattern at every start index, O(n * m).
inline std::vector<int> prefixFunction(const std::string& s) {
    std::vector<int> pi(s.size(), 0);
    for (std::size_t i = 1; i < s.size(); ++i) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) ++k;
        pi[i] = k;
    }
    return pi;
}

inline std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> out;
    const std::size_t m = pattern.size();
    if (m == 0 || m > text.size()) return out;
    const std::vector<int> pi = prefixFunction(pattern);
    std::size_t k = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        while (k > 0 && text[i] != pattern[k]) k = pi[k - 1];
        if (text[i] == pattern[k]) ++k;
        if (k == m) {
            out.push_back(static_cast<int>(i + 1 - m));
            k = pi[k - 1];
        }
    }
    return out;
}
