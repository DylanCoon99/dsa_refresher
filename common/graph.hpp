#pragma once
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<int>>;                           // adjacency list
using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;  // {neighbor, weight}

// edges are {u, v}
inline Graph edges_to_graph(int n, const std::vector<std::vector<int>>& edges, bool directed) {
    Graph g(n);
    for (const auto& e : edges) {
        g[e[0]].push_back(e[1]);
        if (!directed) g[e[1]].push_back(e[0]);
    }
    return g;
}

// edges are {u, v, w}
inline WeightedGraph weighted_edges_to_graph(int n, const std::vector<std::vector<int>>& edges,
                                             bool directed) {
    WeightedGraph g(n);
    for (const auto& e : edges) {
        g[e[0]].emplace_back(e[1], e[2]);
        if (!directed) g[e[1]].emplace_back(e[0], e[2]);
    }
    return g;
}
