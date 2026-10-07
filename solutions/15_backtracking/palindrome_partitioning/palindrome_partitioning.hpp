#pragma once
#include <string>
#include <vector>

// Approach: choose the first piece as any palindromic prefix of the remaining suffix, recurse on the rest.
// Key insight: a split is complete exactly when the start index reaches the end of the string.
// Time: O(n * 2^n)  Space: O(n) beyond the output
// Brute force: try all 2^(n-1) cut masks and test every piece.
namespace palindrome_partitioning_detail {
inline bool is_pal(const std::string& s, int lo, int hi) {  // inclusive bounds
    while (lo < hi)
        if (s[lo++] != s[hi--]) return false;
    return true;
}

inline void rec(const std::string& s, int start, std::vector<std::string>& path,
                std::vector<std::vector<std::string>>& out) {
    if (start == static_cast<int>(s.size())) {
        out.push_back(path);
        return;
    }
    for (int end = start; end < static_cast<int>(s.size()); ++end) {
        if (!is_pal(s, start, end)) continue;
        path.push_back(s.substr(start, end - start + 1));
        rec(s, end + 1, path, out);
        path.pop_back();
    }
}
}  // namespace palindrome_partitioning_detail

inline std::vector<std::vector<std::string>> partition(const std::string& s) {
    std::vector<std::vector<std::string>> out;
    std::vector<std::string> path;
    palindrome_partitioning_detail::rec(s, 0, path, out);
    return out;
}
