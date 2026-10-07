#pragma once
#include <numeric>
#include <vector>

// Approach: add edges in order to a union-find; the first edge whose endpoints are already connected closes the only cycle and is returned.
// Key insight: the graph has exactly one cycle, and scanning left to right the edge that completes it is the last cycle edge in input order.
// Time: O(n alpha(n))  Space: O(n)
// Brute force: for each edge from the last backwards, remove it and check the rest is connected, O(n^2).
inline std::vector<int> findRedundantConnection(const std::vector<std::vector<int>>& edges) {
    std::vector<int> parent(edges.size() + 1);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };
    for (const auto& e : edges) {
        int a = find(e[0]), b = find(e[1]);
        if (a == b) return e;
        parent[a] = b;
    }
    return {};
}
