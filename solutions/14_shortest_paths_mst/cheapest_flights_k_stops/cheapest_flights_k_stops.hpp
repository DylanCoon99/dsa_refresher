#pragma once
#include <algorithm>
#include <limits>
#include <vector>

// Approach: Bellman-Ford limited to k + 1 rounds; each round relaxes every flight against a copy of the previous round's distances.
// Key insight: after round i the distances are the best over trips with at most i flights, so k + 1 rounds enforce the stop limit; a cost-only Dijkstra loses that bound.
// Time: O(k * E)  Space: O(V)
// Brute force: DFS over every route of at most k + 1 flights, O(V^(k+1)).
inline int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k) {
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(n, INF);
    dist[src] = 0;
    for (int round = 0; round <= k; ++round) {
        std::vector<int> next = dist;
        for (const auto& f : flights) {
            if (dist[f[0]] != INF && dist[f[0]] + f[2] < next[f[1]]) next[f[1]] = dist[f[0]] + f[2];
        }
        dist = std::move(next);
    }
    return dist[dst] == INF ? -1 : dist[dst];
}
