#pragma once
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

// Approach: run two multi-source searches uphill from the ocean borders (top/left for the Pacific, bottom/right for the Atlantic), moving to neighbors that are at least as high; cells reached by both are the answer.
// Key insight: reverse the flow. Asking which cells an ocean can reach by climbing is one search per ocean instead of one search per cell.
// Time: O(rows * cols)  Space: O(rows * cols)
// Brute force: from every cell run a separate downhill search to see which oceans it reaches, O((rows * cols)^2).
inline std::vector<std::vector<int>> pacificAtlantic(const std::vector<std::vector<int>>& heights) {
    int rows = static_cast<int>(heights.size()), cols = static_cast<int>(heights[0].size());
    auto reach = [&](bool pacific) {
        std::vector<std::vector<char>> seen(static_cast<std::size_t>(rows), std::vector<char>(static_cast<std::size_t>(cols), 0));
        std::queue<std::pair<int, int>> q;
        auto add = [&](int r, int c) {
            if (!seen[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)]) {
                seen[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = 1;
                q.push({r, c});
            }
        };
        for (int r = 0; r < rows; ++r) add(r, pacific ? 0 : cols - 1);
        for (int c = 0; c < cols; ++c) add(pacific ? 0 : rows - 1, c);
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                if (heights[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] < heights[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)]) continue;
                add(nr, nc);
            }
        }
        return seen;
    };
    auto p = reach(true), a = reach(false);
    std::vector<std::vector<int>> out;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (p[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] && a[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)]) out.push_back({r, c});
    return out;
}
