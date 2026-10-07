#pragma once
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

namespace kruskal_detail {
struct UnionFind {
    std::vector<int> parent, size;
    explicit UnionFind(int n) : parent(n), size(n, 1) { std::iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        int root = x;
        while (parent[root] != root) root = parent[root];
        while (parent[x] != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};
}  // namespace kruskal_detail

// Approach: sort edges by weight; take an edge when union-find says its endpoints are in different components; stop after n - 1 edges.
// Key insight: the lightest edge crossing any cut is safe, and the lightest edge joining two different components crosses the cut around one of them.
// Time: O(E log E)  Space: O(V + E)
// Brute force: Prim with an O(V) scan per step, O(V^2); about 10^10 steps for V = 10^5.
inline long long kruskalMstWeight(int n, std::vector<std::tuple<int, int, int>> edges) {
    std::sort(edges.begin(), edges.end(),
              [](const auto& a, const auto& b) { return std::get<2>(a) < std::get<2>(b); });
    kruskal_detail::UnionFind uf(n);
    long long total = 0;
    int taken = 0;
    for (const auto& [u, v, w] : edges) {
        if (uf.unite(u, v)) {
            total += w;
            if (++taken == n - 1) break;
        }
    }
    return taken == n - 1 ? total : -1;
}
