#pragma once
#include <graph.hpp>

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

inline constexpr long long kUnreachable = std::numeric_limits<long long>::max();

// Approach: min-heap of {distance, vertex}; pop the closest, skip it if stale, relax its out-edges and push every improvement (lazy deletion).
// Key insight: with non-negative weights the first time a vertex is popped its distance is final, because any other route must pass through a vertex that is at least as far.
// Time: O((V + E) log V)  Space: O(V + E)
// Brute force: O(V^2) array scan for the nearest unfinished vertex, or Bellman-Ford O(VE); both are far too slow for V = 10^5, E = 3*10^5.
inline std::vector<long long> dijkstra(int n, const WeightedGraph& adj, int src) {
    std::vector<long long> dist(n, kUnreachable);
    using Item = std::pair<long long, int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> heap;
    dist[src] = 0;
    heap.push({0, src});
    while (!heap.empty()) {
        const auto [d, u] = heap.top();
        heap.pop();
        if (d > dist[u]) continue;  // stale entry
        for (const auto& [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                heap.push({dist[v], v});
            }
        }
    }
    return dist;
}
