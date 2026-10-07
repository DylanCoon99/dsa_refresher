#pragma once
#include <string>

// Approach: ways[i] = (s[i-1] != '0' ? ways[i-1] : 0) + (s[i-2..i) in 10..26 ? ways[i-2] : 0), ways[0] = 1,
//           kept in two rolling unsigned long long variables (intermediate counts can exceed int even
//           when the final answer fits; unsigned wraparound is defined and exact when the answer fits).
// Key insight: the last piece is one or two digits, and each is valid only for a specific digit pattern.
// Time: O(n)  Space: O(1)
// Brute force: recurse over "take one digit / take two digits" without caching: O(fib(n)) calls.
inline int numDecodings(const std::string& s) {
    using u64 = unsigned long long;
    u64 prev2 = 0, prev1 = 1;  // ways for the prefixes of length i-2 and i-1 (length 0 has one way)
    for (std::size_t i = 1; i <= s.size(); ++i) {
        u64 cur = 0;
        if (s[i - 1] != '0') cur += prev1;
        if (i >= 2) {
            int two = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (s[i - 2] != '0' && two <= 26) cur += prev2;
        }
        prev2 = prev1;
        prev1 = cur;
    }
    return static_cast<int>(prev1);
}
