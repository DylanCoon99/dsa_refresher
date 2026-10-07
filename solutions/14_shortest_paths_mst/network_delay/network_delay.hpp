#pragma once
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// Approach: Dijkstra from k over the directed links; the answer is the largest finite distance, or -1 if any node stays unreached.
// Key insight: "time until everyone has the signal" is the maximum shortest-path distance from the source.
// Time: O((V + E) log V)  Space: O(V + E)
// Brute force: Bellman-Ford / Floyd-Warshall, O(VE) or O(V^3); fine at n = 100 but heavier than needed.
inline int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    for (const auto& t : times) adj[t[0]].emplace_back(t[1], t[2]);
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(n + 1, INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
    dist[k] = 0;
    heap.push({0, k});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) {
                dist[v] = d + w;
                heap.push({dist[v], v});
            }
    }
    int worst = 0;
    for (int v = 1; v <= n; ++v) {
        if (dist[v] == INF) return -1;
        worst = std::max(worst, dist[v]);
    }
    return worst;
}
