#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: L[i][j] = LCS of a[0..i) and b[0..j). Equal last chars: 1 + L[i-1][j-1]; otherwise
//           max(L[i-1][j], L[i][j-1]). L[0][*] = L[*][0] = 0. Memo recurses from (|a|, |b|); Tab
//           fills rows 0..|a|.
// Key insight: if the last characters match, matching them is never worse; if not, one of them is unused.
// Time: O(|a||b|)  Space: O(|a||b|)
// Brute force: try every subsequence of a (2^|a|) against b, or the same recursion without a cache.
namespace lcs_detail {
inline int rec(const std::string& a, const std::string& b, int i, int j, std::vector<std::vector<int>>& cache) {
    if (i == 0 || j == 0) return 0;
    int& slot = cache[i][j];
    if (slot != -1) return slot;
    if (a[i - 1] == b[j - 1]) return slot = 1 + rec(a, b, i - 1, j - 1, cache);
    return slot = std::max(rec(a, b, i - 1, j, cache), rec(a, b, i, j - 1, cache));
}
}  // namespace lcs_detail

inline int lcsMemo(const std::string& a, const std::string& b) {
    const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size());
    std::vector<std::vector<int>> cache(n + 1, std::vector<int>(m + 1, -1));
    return lcs_detail::rec(a, b, n, m, cache);
}

inline int lcsTab(const std::string& a, const std::string& b) {
    const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size());
    std::vector<std::vector<int>> L(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            L[i][j] = a[i - 1] == b[j - 1] ? L[i - 1][j - 1] + 1 : std::max(L[i - 1][j], L[i][j - 1]);
    return L[n][m];
}
