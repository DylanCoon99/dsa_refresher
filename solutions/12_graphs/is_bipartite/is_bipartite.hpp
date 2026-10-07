#pragma once
#include <cstddef>
#include <queue>
#include <vector>

// Approach: two-color each component with BFS, giving every neighbor the opposite color; a neighbor that already has the same color means an odd cycle.
// Key insight: a graph is bipartite exactly when it has no odd cycle, and BFS coloring finds one the moment an edge joins two same-colored vertices.
// Time: O(V + E)  Space: O(V)
// Brute force: try all 2^V assignments of vertices to two groups and check every edge, O(2^V * E).
inline bool isBipartite(const std::vector<std::vector<int>>& graph) {
    std::vector<int> color(graph.size(), -1);
    for (std::size_t s = 0; s < graph.size(); ++s) {
        if (color[s] != -1) continue;
        color[s] = 0;
        std::queue<int> q;
        q.push(static_cast<int>(s));
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : graph[static_cast<std::size_t>(v)]) {
                if (color[static_cast<std::size_t>(w)] == -1) {
                    color[static_cast<std::size_t>(w)] = 1 - color[static_cast<std::size_t>(v)];
                    q.push(w);
                } else if (color[static_cast<std::size_t>(w)] == color[static_cast<std::size_t>(v)]) {
                    return false;
                }
            }
        }
    }
    return true;
}
