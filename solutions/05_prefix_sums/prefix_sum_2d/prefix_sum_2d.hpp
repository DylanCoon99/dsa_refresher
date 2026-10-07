#pragma once
#include <vector>

// Approach: P[i][j] holds the sum of the top-left i x j block; a query is
//           P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1].
// Key insight: a rectangle is a big corner rectangle minus two strips, plus the doubly-removed corner.
// Time: O(rows*cols) build, O(1) query  Space: O(rows*cols)
// Brute force: add up every cell of the query rectangle, O(rows*cols) per query.
class PrefixSum2D {
public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& grid)
        : p_(grid.size() + 1, std::vector<long long>(grid[0].size() + 1, 0)) {
        for (std::size_t i = 0; i < grid.size(); ++i)
            for (std::size_t j = 0; j < grid[0].size(); ++j)
                p_[i + 1][j + 1] = grid[i][j] + p_[i][j + 1] + p_[i + 1][j] - p_[i][j];
    }

    long long sumRegion(int r1, int c1, int r2, int c2) const {
        return p_[r2 + 1][c2 + 1] - p_[r1][c2 + 1] - p_[r2 + 1][c1] + p_[r1][c1];
    }

private:
    std::vector<std::vector<long long>> p_;
};
