#pragma once
#include <string>
#include <vector>

// Approach: DFS from every cell; mark the current cell (overwrite with '#') while exploring, restore on return.
// Key insight: the in-place mark is the "choose", restoring the letter is the "unchoose".
// Time: O(R * C * 3^L)  Space: O(L)
// Brute force: enumerate every simple path of length L from every cell, same exponential bound without pruning.
namespace word_search_detail {
inline bool dfs(std::vector<std::vector<char>>& b, const std::string& w, int r, int c, std::size_t i) {
    if (r < 0 || c < 0 || r >= static_cast<int>(b.size()) || c >= static_cast<int>(b[0].size())) return false;
    if (b[r][c] != w[i]) return false;
    if (i + 1 == w.size()) return true;
    const char saved = b[r][c];
    b[r][c] = '#';
    const bool found = dfs(b, w, r + 1, c, i + 1) || dfs(b, w, r - 1, c, i + 1) ||
                       dfs(b, w, r, c + 1, i + 1) || dfs(b, w, r, c - 1, i + 1);
    b[r][c] = saved;
    return found;
}
}  // namespace word_search_detail

inline bool exist(std::vector<std::vector<char>> board, const std::string& word) {
    if (word.empty()) return true;
    for (int r = 0; r < static_cast<int>(board.size()); ++r)
        for (int c = 0; c < static_cast<int>(board[0].size()); ++c)
            if (word_search_detail::dfs(board, word, r, c, 0)) return true;
    return false;
}
