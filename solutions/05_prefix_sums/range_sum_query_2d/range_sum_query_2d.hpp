#pragma once
#include <vector>

// Approach: P[i][j] is the sum of the top-left i x j block; a query is
//           P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1].
// Key insight: a rectangle is a corner block minus two strips, plus the corner subtracted twice.
// Time: O(rows*cols) build, O(1) query  Space: O(rows*cols)
// Brute force: add up every cell of the query rectangle, O(rows*cols) per query.
class NumMatrix {
public:
    explicit NumMatrix(const std::vector<std::vector<int>>& matrix)
        : p_(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0)) {
        for (std::size_t i = 0; i < matrix.size(); ++i)
            for (std::size_t j = 0; j < matrix[0].size(); ++j)
                p_[i + 1][j + 1] = matrix[i][j] + p_[i][j + 1] + p_[i + 1][j] - p_[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2) const {
        return p_[row2 + 1][col2 + 1] - p_[row1][col2 + 1] - p_[row2 + 1][col1] + p_[row1][col1];
    }

private:
    std::vector<std::vector<int>> p_;
};
