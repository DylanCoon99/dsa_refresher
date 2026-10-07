#pragma once
#include <vector>

// Approach: paths[r][c] = paths[r-1][c] + paths[r][c-1], first row and column are 1; one rolling row.
// Key insight: every path enters a cell from above or from the left, so the counts just add.
// Time: O(m * n)  Space: O(n)
// Brute force: recurse down/right from the start without caching: C(m+n-2, m-1) leaf calls.
inline int uniquePaths(int m, int n) {
    std::vector<int> row(n, 1);
    for (int r = 1; r < m; ++r)
        for (int c = 1; c < n; ++c) row[c] += row[c - 1];
    return row[n - 1];
}
