#pragma once
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

// Approach: Dijkstra over the grid where a route's cost is the maximum step so far (max replaces +); pop the cheapest cell and relax its four neighbours.
// Key insight: the "minimize the worst edge" objective still satisfies Dijkstra's greedy property, since extending a route never lowers its cost.
// Time: O(R C log(R C))  Space: O(R C)
// Brute force: DFS over every simple route tracking the maximum step, exponential in R * C.
inline int minimumEffortPath(const std::vector<std::vector<int>>& heights) {
    int rows = static_cast<int>(heights.size()), cols = static_cast<int>(heights[0].size());
    std::vector<std::vector<int>> best(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    using Item = std::tuple<int, int, int>;  // effort, r, c
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> heap;
    best[0][0] = 0;
    heap.push({0, 0, 0});
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!heap.empty()) {
        auto [e, r, c] = heap.top();
        heap.pop();
        if (e > best[r][c]) continue;
        if (r == rows - 1 && c == cols - 1) return e;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
            int ne = std::max(e, std::abs(heights[nr][nc] - heights[r][c]));
            if (ne < best[nr][nc]) {
                best[nr][nc] = ne;
                heap.push({ne, nr, nc});
            }
        }
    }
    return 0;
}
