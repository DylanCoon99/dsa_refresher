#pragma once
#include <numeric>
#include <vector>

// Approach: union-find over the nodes; start with n components and subtract one for every edge that joins two different sets.
// Key insight: each successful union lowers the component count by exactly one, and a repeated or cycle-closing edge never does.
// Time: O((n + E) alpha(n))  Space: O(n)
// Brute force: DFS/BFS from every unvisited node, O(n + E) as well; the union-find version also handles edges arriving one at a time.
inline int countComponents(int n, const std::vector<std::vector<int>>& edges) {
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };
    int count = n;
    for (const auto& e : edges) {
        int a = find(e[0]), b = find(e[1]);
        if (a != b) {
            parent[a] = b;
            --count;
        }
    }
    return count;
}
