#pragma once
#include <algorithm>
#include <vector>

// Approach: sort, backtrack over positions with start = i + 1 (each used once); at each level skip a
//           value equal to the previous one tried there, and stop once a candidate exceeds the remainder.
// Key insight: sorting makes equal values adjacent, so "skip if same as the previous sibling" removes repeats.
// Time: proportional to the distinct combinations explored  Space: O(n) beyond the output
// Brute force: enumerate all 2^n position subsets and dedupe with a set, O(n * 2^n).
namespace combination_sum_ii_detail {
inline void rec(const std::vector<int>& c, int start, int remaining, std::vector<int>& path,
                std::vector<std::vector<int>>& out) {
    if (remaining == 0) {
        out.push_back(path);
        return;
    }
    for (int i = start; i < static_cast<int>(c.size()); ++i) {
        if (c[i] > remaining) break;
        if (i > start && c[i] == c[i - 1]) continue;
        path.push_back(c[i]);
        rec(c, i + 1, remaining - c[i], path, out);
        path.pop_back();
    }
}
}  // namespace combination_sum_ii_detail

inline std::vector<std::vector<int>> combinationSum2(std::vector<int> candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    std::vector<std::vector<int>> out;
    std::vector<int> path;
    combination_sum_ii_detail::rec(candidates, 0, target, path, out);
    return out;
}
