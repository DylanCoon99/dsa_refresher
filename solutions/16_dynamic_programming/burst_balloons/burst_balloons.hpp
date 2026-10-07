#pragma once
#include <algorithm>
#include <vector>

// Approach: pad with 1 at both ends; best[i][j] = max coins from bursting everything strictly between i and j.
//           Choosing k as the LAST balloon burst in (i, j): best[i][k] + best[k][j] + a[i]*a[k]*a[j].
//           Filled by increasing gap j - i.
// Key insight: picking the last balloon to burst makes its neighbours known (the range ends) and splits the rest
//              into two independent ranges.
// Time: O(n^3)  Space: O(n^2)
// Brute force: try every bursting order: O(n!).
inline int maxCoins(const std::vector<int>& nums) {
    std::vector<int> a;
    a.push_back(1);
    a.insert(a.end(), nums.begin(), nums.end());
    a.push_back(1);
    const int m = static_cast<int>(a.size());
    std::vector<std::vector<int>> best(m, std::vector<int>(m, 0));
    for (int gap = 2; gap < m; ++gap)
        for (int i = 0; i + gap < m; ++i) {
            const int j = i + gap;
            for (int k = i + 1; k < j; ++k)
                best[i][j] = std::max(best[i][j], best[i][k] + best[k][j] + a[i] * a[k] * a[j]);
        }
    return best[0][m - 1];
}
