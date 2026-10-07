#pragma once
#include <string>
#include <vector>

// Approach: build the prefix function of needle, then scan haystack keeping the current match length; stop at the first full match.
// Key insight: on a mismatch the matched part of the text is also a prefix of the needle, so fall back to its longest border instead of re-reading text.
// Time: O(n + m)  Space: O(m)
// Brute force: try the needle at every start index, O(n * m).
inline int strStr(const std::string& haystack, const std::string& needle) {
    const std::size_t m = needle.size();
    if (m == 0) return 0;
    if (m > haystack.size()) return -1;
    std::vector<int> pi(m, 0);
    for (std::size_t i = 1; i < m; ++i) {
        int k = pi[i - 1];
        while (k > 0 && needle[i] != needle[k]) k = pi[k - 1];
        if (needle[i] == needle[k]) ++k;
        pi[i] = k;
    }
    std::size_t k = 0;
    for (std::size_t i = 0; i < haystack.size(); ++i) {
        while (k > 0 && haystack[i] != needle[k]) k = pi[k - 1];
        if (haystack[i] == needle[k]) ++k;
        if (k == m) return static_cast<int>(i + 1 - m);
    }
    return -1;
}
