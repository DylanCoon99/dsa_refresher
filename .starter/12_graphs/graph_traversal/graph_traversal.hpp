#pragma once
#include <graph.hpp>

#include <string>
#include <vector>

// Vertices reachable from `start`, in BFS order. Neighbors are visited in adjacency-list order.
inline std::vector<int> bfsOrder(const Graph& adj, int start) {
    // TODO: implement
    return {};
}

// Vertices reachable from `start`, in DFS preorder. Neighbors are tried in adjacency-list order.
inline std::vector<int> dfsOrder(const Graph& adj, int start) {
    // TODO: implement
    return {};
}

// Shortest 4-directional distance from (sr, sc) to every cell. '.' is open, '#' is a wall.
// Walls and unreachable cells are -1.
inline std::vector<std::vector<int>> gridDistances(const std::vector<std::string>& grid, int sr, int sc) {
    // TODO: implement
    return {};
}

// Number of 4-connected regions of '.' cells.
inline int countRegions(const std::vector<std::string>& grid) {
    // TODO: implement
    return 0;
}
