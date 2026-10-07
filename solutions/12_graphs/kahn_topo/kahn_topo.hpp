#pragma once
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

// Approach: count incoming edges per vertex, repeatedly remove a vertex with none (queue) and decrement its successors; if fewer than n vertices come out, a cycle remains.
// Key insight: a vertex with in-degree 0 can safely go first, and a cycle is exactly what keeps every remaining vertex's in-degree above 0.
// Time: O(V + E)  Space: O(V + E)
// Brute force: repeatedly rescan every edge to find a vertex with no remaining incoming edge, O(V * (V + E)).
inline std::vector<int> topoSortKahn(int n, const std::vector<std::pair<int, int>>& edges) {
    std::vector<std::vector<int>> adj(static_cast<std::size_t>(n));
    std::vector<int> indeg(static_cast<std::size_t>(n), 0);
    for (const auto& [u, v] : edges) {
        adj[static_cast<std::size_t>(u)].push_back(v);
        ++indeg[static_cast<std::size_t>(v)];
    }
    std::queue<int> ready;
    for (int v = 0; v < n; ++v)
        if (indeg[static_cast<std::size_t>(v)] == 0) ready.push(v);
    std::vector<int> order;
    while (!ready.empty()) {
        int v = ready.front();
        ready.pop();
        order.push_back(v);
        for (int w : adj[static_cast<std::size_t>(v)])
            if (--indeg[static_cast<std::size_t>(w)] == 0) ready.push(w);
    }
    if (static_cast<int>(order.size()) != n) return {};
    return order;
}
