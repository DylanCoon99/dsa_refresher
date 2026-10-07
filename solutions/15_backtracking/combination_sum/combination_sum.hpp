#pragma once
#include <algorithm>
#include <vector>

// Approach: sort, then backtrack over candidate indices; recurse from the same index i to allow reuse.
// Key insight: never moving to a lower index makes {2,3} and {3,2} the same single path.
// Time: exponential in target / min(candidates), output-sensitive  Space: O(target / min) beyond the output
// Brute force: DP over sums holding the set of multisets for each total.
namespace combination_sum_detail {
inline void rec(const std::vector<int>& c, int start, int remaining, std::vector<int>& path,
                std::vector<std::vector<int>>& out) {
    if (remaining == 0) {
        out.push_back(path);
        return;
    }
    for (int i = start; i < static_cast<int>(c.size()); ++i) {
        if (c[i] > remaining) break;  // sorted: every later candidate is too big as well
        path.push_back(c[i]);
        rec(c, i, remaining - c[i], path, out);  // i, not i + 1: reuse allowed
        path.pop_back();
    }
}
}  // namespace combination_sum_detail

inline std::vector<std::vector<int>> combinationSum(const std::vector<int>& candidates, int target) {
    std::vector<int> c = candidates;
    std::sort(c.begin(), c.end());
    std::vector<std::vector<int>> out;
    std::vector<int> path;
    combination_sum_detail::rec(c, 0, target, path, out);
    return out;
}
