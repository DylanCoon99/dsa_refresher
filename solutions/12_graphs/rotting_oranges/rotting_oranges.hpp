#pragma once
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

// Approach: multi-source BFS. Start with every rotten orange in the queue, process the queue one level (minute) at a time, rot fresh neighbors, and count the fresh oranges left.
// Key insight: oranges rot simultaneously, so seeding the queue with all rotten cells at once makes BFS depth equal elapsed minutes.
// Time: O(rows * cols)  Space: O(rows * cols)
// Brute force: for each fresh orange run its own BFS to the nearest rotten orange and take the maximum, O((rows * cols)^2).
inline int orangesRotting(std::vector<std::vector<int>> grid) {
    int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
    std::queue<std::pair<int, int>> q;
    int fresh = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            int v = grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
            if (v == 2) q.push({i, j});
            if (v == 1) ++fresh;
        }
    int minutes = 0;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty() && fresh > 0) {
        ++minutes;
        for (std::size_t left = q.size(); left > 0; --left) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                if (grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != 1) continue;
                grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] = 2;
                --fresh;
                q.push({nr, nc});
            }
        }
    }
    return fresh == 0 ? minutes : -1;
}
