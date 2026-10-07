#pragma once
#include <cstddef>
#include <utility>
#include <vector>

// Approach: scan the grid; at each unvisited land cell count one island and flood-fill it with an explicit stack, sinking cells as they are visited.
// Key insight: each island is discovered exactly once, at its first cell in scan order, because the flood fill marks all of it.
// Time: O(rows * cols)  Space: O(rows * cols)
// Brute force: for each land cell, flood-fill its island with a fresh visited array and count the cell only if it is the first cell of that island, O((rows * cols)^2).
inline int numIslands(std::vector<std::vector<char>> grid) {
    int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
    int islands = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] != '1') continue;
            ++islands;
            grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = '0';
            std::vector<std::pair<int, int>> stack{{i, j}};
            while (!stack.empty()) {
                auto [r, c] = stack.back();
                stack.pop_back();
                const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                    if (grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != '1') continue;
                    grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] = '0';
                    stack.push_back({nr, nc});
                }
            }
        }
    }
    return islands;
}
