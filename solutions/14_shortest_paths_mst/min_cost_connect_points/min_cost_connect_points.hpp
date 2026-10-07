#pragma once
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <vector>

// Approach: dense Prim; keep for each outside point its cheapest Manhattan distance to the tree, repeatedly add the closest one and update the rest.
// Key insight: the complete graph is dense, so an O(V^2) Prim with no heap beats sorting all V^2 edges.
// Time: O(n^2)  Space: O(n)
// Brute force: enumerate all spanning trees (Cayley: n^(n-2)), or at every step rescan all (tree, outside) pairs for the cheapest, O(n^3).
inline int minCostConnectPoints(const std::vector<std::vector<int>>& points) {
    int n = static_cast<int>(points.size());
    std::vector<int> best(n, std::numeric_limits<int>::max());
    std::vector<bool> inTree(n, false);
    best[0] = 0;
    int total = 0;
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!inTree[v] && (u == -1 || best[v] < best[u])) u = v;
        inTree[u] = true;
        total += best[u];
        for (int v = 0; v < n; ++v) {
            if (inTree[v]) continue;
            int d = std::abs(points[u][0] - points[v][0]) + std::abs(points[u][1] - points[v][1]);
            if (d < best[v]) best[v] = d;
        }
    }
    return total;
}
