#pragma once
#include <vector>

// Approach: three-color DFS. A vertex is safe once all its out-neighbors are proven safe; reaching a gray vertex
//           (one on the current path) means a cycle, so the whole path is unsafe. Colors are memoized.
// Key insight: "safe" is the opposite of "can reach a cycle", and each vertex's verdict only has to be computed once.
//              (Equivalent: run Kahn's algorithm on the reversed graph; the vertices that get removed are safe.)
// Time: O(V + E)  Space: O(V) (recursion depth up to V; production code would use an explicit stack)
// Brute force: the same DFS without memoizing verdicts re-explores shared paths, exponential on layered graphs.
namespace safe_detail {
// 0 = unvisited, 1 = on the current path, 2 = safe, 3 = unsafe
inline bool isSafe(int u, const std::vector<std::vector<int>>& g, std::vector<int>& color) {
    if (color[u] == 2) return true;
    if (color[u] == 1 || color[u] == 3) return false;
    color[u] = 1;
    for (int v : g[u]) {
        if (!isSafe(v, g, color)) {
            color[u] = 3;
            return false;
        }
    }
    color[u] = 2;
    return true;
}
}  // namespace safe_detail

inline std::vector<int> eventualSafeNodes(const std::vector<std::vector<int>>& graph) {
    int n = static_cast<int>(graph.size());
    std::vector<int> color(n, 0), res;
    for (int u = 0; u < n; ++u)
        if (safe_detail::isSafe(u, graph, color)) res.push_back(u);
    return res;
}
