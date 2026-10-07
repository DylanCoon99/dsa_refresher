#pragma once
#include <graph.hpp>

#include <algorithm>
#include <utility>
#include <vector>

// Approach: one DFS records discovery times tin[v] and low[v] (the earliest discovery time reachable from v's
//           subtree using at most one back edge). A tree edge (p, c) is a bridge when low[c] > tin[p]; a non-root p
//           is a cut vertex when some child has low[c] >= tin[p]; a root is one when it has 2+ DFS children.
// Key insight: skip the parent by EDGE INDEX, not by parent vertex, or a doubled edge would wrongly look like a bridge.
// Time: O(V + E)  Space: O(V + E) (recursion depth up to V; production code would use an explicit stack)
// Brute force: delete each edge (or vertex) and count components again, O(E * (V + E)).
namespace tarjan_detail {
struct Dfs {
    const Graph& adj;
    std::vector<std::vector<std::pair<int, int>>> arcs;  // (neighbor, edge id)
    std::vector<int> tin, low;
    std::vector<std::pair<int, int>> bridges;
    std::vector<char> cut;
    int timer = 0;

    Dfs(int n, const Graph& g) : adj(g), arcs(n), tin(n, -1), low(n, 0), cut(n, 0) {
        // Give each undirected edge one id. Both directions of a repeated edge get their own ids.
        std::vector<std::vector<int>> used(n);
        int id = 0;
        for (int u = 0; u < n; ++u) used[u].assign(adj[u].size(), 0);
        for (int u = 0; u < n; ++u) {
            for (std::size_t i = 0; i < adj[u].size(); ++i) {
                if (used[u][i]) continue;
                int v = adj[u][i];
                used[u][i] = 1;
                // find the matching unused entry u in v's list
                for (std::size_t j = 0; j < adj[v].size(); ++j) {
                    if (adj[v][j] == u && !used[v][j]) {
                        used[v][j] = 1;
                        break;
                    }
                }
                arcs[u].push_back({v, id});
                arcs[v].push_back({u, id});
                ++id;
            }
        }
    }

    void dfs(int v, int parentEdge) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [to, id] : arcs[v]) {
            if (id == parentEdge) continue;
            if (tin[to] != -1) {
                low[v] = std::min(low[v], tin[to]);
            } else {
                dfs(to, id);
                ++children;
                low[v] = std::min(low[v], low[to]);
                if (low[to] > tin[v]) bridges.push_back({std::min(v, to), std::max(v, to)});
                if (parentEdge != -1 && low[to] >= tin[v]) cut[v] = 1;
            }
        }
        if (parentEdge == -1 && children >= 2) cut[v] = 1;
    }

    void run(int n) {
        for (int v = 0; v < n; ++v)
            if (tin[v] == -1) dfs(v, -1);
    }
};
}  // namespace tarjan_detail

inline std::vector<std::pair<int, int>> findBridges(int n, const Graph& adj) {
    tarjan_detail::Dfs d(n, adj);
    d.run(n);
    return d.bridges;
}

inline std::vector<int> findArticulationPoints(int n, const Graph& adj) {
    tarjan_detail::Dfs d(n, adj);
    d.run(n);
    std::vector<int> res;
    for (int v = 0; v < n; ++v)
        if (d.cut[v]) res.push_back(v);
    return res;
}
