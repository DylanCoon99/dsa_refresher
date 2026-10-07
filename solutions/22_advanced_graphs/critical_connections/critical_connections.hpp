#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Approach: one DFS computes discovery times tin[v] and low[v] (earliest discovery time reachable from v's subtree
//           through tree edges plus at most one back edge). A tree edge (p, c) is critical exactly when low[c] > tin[p].
// Key insight: low[c] > tin[p] means nothing in c's subtree climbs back to p or above, so (p, c) is the only link.
// Time: O(V + E)  Space: O(V + E) (recursion depth up to V; production code would use an explicit stack)
// Brute force: remove each connection and re-run a connectivity check, O(E * (V + E)).
namespace critical_detail {
struct Dfs {
    std::vector<std::vector<std::pair<int, int>>> adj;  // (neighbor, connection id)
    std::vector<int> tin, low;
    std::vector<std::vector<int>> out;
    int timer = 0;
    void dfs(int v, int parentEdge) {
        tin[v] = low[v] = timer++;
        for (auto [to, id] : adj[v]) {
            if (id == parentEdge) continue;
            if (tin[to] != -1) {
                low[v] = std::min(low[v], tin[to]);
            } else {
                dfs(to, id);
                low[v] = std::min(low[v], low[to]);
                if (low[to] > tin[v]) out.push_back({v, to});
            }
        }
    }
};
}  // namespace critical_detail

inline std::vector<std::vector<int>> criticalConnections(int n, const std::vector<std::vector<int>>& connections) {
    critical_detail::Dfs d;
    d.adj.assign(n, {});
    d.tin.assign(n, -1);
    d.low.assign(n, 0);
    for (int i = 0; i < static_cast<int>(connections.size()); ++i) {
        d.adj[connections[i][0]].push_back({connections[i][1], i});
        d.adj[connections[i][1]].push_back({connections[i][0], i});
    }
    for (int v = 0; v < n; ++v)
        if (d.tin[v] == -1) d.dfs(v, -1);
    return d.out;
}
