#pragma once
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

// Approach: for every land cell, flood-fill its island with an explicit stack while counting the cells, sinking each cell as it is visited; keep the maximum count.
// Key insight: sinking cells as you visit them is the visited set, so each cell is expanded once and each island is measured once.
// Time: O(rows * cols)  Space: O(rows * cols)
// Brute force: measure each island from every one of its cells with a fresh visited array, O((rows * cols)^2).
inline int maxAreaOfIsland(std::vector<std::vector<int>> grid) {
    int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
    int best = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] != 1) continue;
            int area = 0;
            grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = 0;
            std::vector<std::pair<int, int>> stack{{i, j}};
            while (!stack.empty()) {
                auto [r, c] = stack.back();
                stack.pop_back();
                ++area;
                const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                    if (grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != 1) continue;
                    grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] = 0;
                    stack.push_back({nr, nc});
                }
            }
            best = std::max(best, area);
        }
    }
    return best;
}
