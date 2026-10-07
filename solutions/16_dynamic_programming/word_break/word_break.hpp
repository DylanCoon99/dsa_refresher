#pragma once
#include <string>
#include <vector>

// Approach: ok[i] = some word w ends at i with ok[i - |w|] true; ok[0] = true.
// Key insight: whether a prefix is splittable doesn't depend on how it was split, so each position is solved once.
// Time: O(n * W * L)  Space: O(n)
// Brute force: recurse over every word that matches at each position without caching: exponential.
inline bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict) {
    const std::size_t n = s.size();
    std::vector<char> ok(n + 1, 0);
    ok[0] = 1;
    for (std::size_t i = 1; i <= n; ++i)
        for (const std::string& w : wordDict)
            if (w.size() <= i && ok[i - w.size()] && s.compare(i - w.size(), w.size(), w) == 0) {
                ok[i] = 1;
                break;
            }
    return ok[n];
}
