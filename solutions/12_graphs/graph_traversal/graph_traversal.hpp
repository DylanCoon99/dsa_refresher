#pragma once
#include <graph.hpp>

#include <cstddef>
#include <queue>
#include <string>
#include <utility>
#include <vector>

// Approach: BFS with a queue and a visited array; DFS with an explicit stack that pushes neighbors in reverse and marks a vertex visited when it is popped, which reproduces recursive preorder. Grids use the same BFS on an implicit graph.
// Key insight: mark visited when you enqueue (BFS) or pop (DFS) so every vertex is processed once; BFS layers are exactly the shortest unweighted distances.
// Time: O(V + E) for graphs, O(rows * cols) for grids  Space: O(V)
// Brute force: for each cell, run a fresh BFS from the start (gridDistances) or from that cell (countRegions) with its own visited array, O((rows * cols)^2).
inline std::vector<int> bfsOrder(const Graph& adj, int start) {
    std::vector<char> seen(adj.size(), 0);
    std::vector<int> order;
    std::queue<int> q;
    q.push(start);
    seen[static_cast<std::size_t>(start)] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : adj[static_cast<std::size_t>(v)]) {
            if (!seen[static_cast<std::size_t>(w)]) {
                seen[static_cast<std::size_t>(w)] = 1;
                q.push(w);
            }
        }
    }
    return order;
}

inline std::vector<int> dfsOrder(const Graph& adj, int start) {
    std::vector<char> seen(adj.size(), 0);
    std::vector<int> order;
    std::vector<int> stack{start};
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (seen[static_cast<std::size_t>(v)]) continue;
        seen[static_cast<std::size_t>(v)] = 1;
        order.push_back(v);
        const auto& nb = adj[static_cast<std::size_t>(v)];
        for (auto it = nb.rbegin(); it != nb.rend(); ++it) {
            if (!seen[static_cast<std::size_t>(*it)]) stack.push_back(*it);
        }
    }
    return order;
}

inline std::vector<std::vector<int>> gridDistances(const std::vector<std::string>& grid, int sr, int sc) {
    int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
    std::vector<std::vector<int>> dist(static_cast<std::size_t>(rows), std::vector<int>(static_cast<std::size_t>(cols), -1));
    std::queue<std::pair<int, int>> q;
    dist[static_cast<std::size_t>(sr)][static_cast<std::size_t>(sc)] = 0;
    q.push({sr, sc});
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
            if (grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != '.') continue;
            if (dist[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != -1) continue;
            dist[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] = dist[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}

inline int countRegions(const std::vector<std::string>& grid) {
    int rows = static_cast<int>(grid.size()), cols = static_cast<int>(grid[0].size());
    std::vector<std::vector<char>> seen(static_cast<std::size_t>(rows), std::vector<char>(static_cast<std::size_t>(cols), 0));
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    int regions = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] != '.' || seen[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)]) continue;
            ++regions;
            std::vector<std::pair<int, int>> stack{{i, j}};
            seen[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = 1;
            while (!stack.empty()) {
                auto [r, c] = stack.back();
                stack.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                    if (grid[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] != '.') continue;
                    if (seen[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)]) continue;
                    seen[static_cast<std::size_t>(nr)][static_cast<std::size_t>(nc)] = 1;
                    stack.push_back({nr, nc});
                }
            }
        }
    }
    return regions;
}
