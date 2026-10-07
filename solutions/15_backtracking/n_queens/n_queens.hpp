#pragma once
#include <string>
#include <vector>

// Approach: place one queen per row; boolean arrays for columns, "/" diagonals (r + c) and "\" diagonals
//           (r - c + n - 1) make the safety check O(1).
// Key insight: rows are handled by the recursion itself, so only columns and the two diagonals need tracking.
// Time: roughly O(n!)  Space: O(n) beyond the output
// Brute force: try every n-subset of the n^2 squares and test all pairs, O(C(n^2, n) * n^2).
namespace n_queens_detail {
inline void rec(int n, int row, std::vector<bool>& col, std::vector<bool>& d1, std::vector<bool>& d2,
                std::vector<std::string>& board, std::vector<std::vector<std::string>>& out) {
    if (row == n) {
        out.push_back(board);
        return;
    }
    for (int c = 0; c < n; ++c) {
        if (col[c] || d1[row + c] || d2[row - c + n - 1]) continue;
        col[c] = d1[row + c] = d2[row - c + n - 1] = true;
        board[row][c] = 'Q';
        rec(n, row + 1, col, d1, d2, board, out);
        board[row][c] = '.';
        col[c] = d1[row + c] = d2[row - c + n - 1] = false;
    }
}
}  // namespace n_queens_detail

inline std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> out;
    std::vector<bool> col(n, false), d1(2 * n, false), d2(2 * n, false);
    std::vector<std::string> board(n, std::string(n, '.'));
    n_queens_detail::rec(n, 0, col, d1, d2, board, out);
    return out;
}
