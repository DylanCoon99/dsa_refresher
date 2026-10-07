#pragma once
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

// Approach: Dijkstra on the grid where a route's cost is the highest elevation seen so far; the first time the bottom-right cell is popped its cost is the answer.
// Key insight: the time needed for a route is the maximum cell on it, and a min-max path is found by the same greedy "pop the cheapest frontier cell" as Dijkstra.
// Time: O(n^2 log n)  Space: O(n^2)
// Brute force: DFS over every simple route tracking the maximum elevation, exponential in n^2.
inline int swimInWater(const std::vector<std::vector<int>>& grid) {
    int n = static_cast<int>(grid.size());
    std::vector<std::vector<int>> best(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    using Item = std::tuple<int, int, int>;  // level, r, c
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> heap;
    best[0][0] = grid[0][0];
    heap.push({grid[0][0], 0, 0});
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!heap.empty()) {
        auto [t, r, c] = heap.top();
        heap.pop();
        if (t > best[r][c]) continue;
        if (r == n - 1 && c == n - 1) return t;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            int nt = std::max(t, grid[nr][nc]);
            if (nt < best[nr][nc]) {
                best[nr][nc] = nt;
                heap.push({nt, nr, nc});
            }
        }
    }
    return -1;
}
