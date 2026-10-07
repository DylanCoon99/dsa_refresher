#pragma once
#include <graph.hpp>

#include <limits>
#include <vector>

inline constexpr long long kUnreachable = std::numeric_limits<long long>::max();

// adj[u] = {v, w}: a directed edge u -> v of weight w >= 0.
// Returns dist[0..n-1] from src (dist[src] = 0), or kUnreachable where there is no path.
inline std::vector<long long> dijkstra(int n, const WeightedGraph& adj, int src) {
    // TODO: implement
    return {};
}
