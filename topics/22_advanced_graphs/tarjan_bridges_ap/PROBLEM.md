# Tarjan's Algorithm: Bridges and Articulation Points
**Topic:** 22 Advanced Graph Topics · **Kind:** Implement · **Difficulty:** Hard

## Problem
`Graph` is `std::vector<std::vector<int>>`. The input is an **undirected** graph on vertices `0..n-1`: `adj[v]` lists the neighbors of `v`, and every edge `{u, v}` appears in both `adj[u]` and `adj[v]`. The graph may be disconnected and may have **repeated (parallel) edges**: an edge listed twice in each endpoint's list is two separate edges. There are no self-loops.

Implement two functions:

```cpp
std::vector<std::pair<int,int>> findBridges(int n, const Graph& adj);
std::vector<int> findArticulationPoints(int n, const Graph& adj);
```

- A **bridge** is an edge whose removal increases the number of connected components. Return each bridge once, as `(min, max)`. A doubled edge is never a bridge, because the other copy still connects its endpoints; so decide "is this the edge I came from" by edge, not by parent vertex.
- An **articulation point** (cut vertex) is a vertex whose removal, together with its edges, increases the number of connected components among the remaining vertices. An isolated vertex is not one.

Both results may be in any order.

## Examples
- Two triangles `0-1-2` and `3-4-5` joined by the edge `2-3` → bridges `{(2,3)}`, articulation points `{2, 3}`.
- The path `0-1-2-3` → bridges `{(0,1), (1,2), (2,3)}`, articulation points `{1, 2}`.
- `0 = 1` (two parallel edges) plus `1-2` → bridges `{(1,2)}`, articulation points `{1}`.

## Constraints
- 0 ≤ n ≤ 2·10⁴ and up to 6·10⁴ edges (limits chosen for this exercise; the largest test uses exactly these).
- No self-loops; parallel edges are allowed.
- The reference solution uses recursive DFS, and the largest test has DFS depth of up to roughly 10⁴. For production code on deep graphs, write the DFS with an explicit stack.

## Target
Time: O(V + E) · Space: O(V + E)

## CLRS (optional, ≈20 min)
- Ch. 22 (3e) / Ch. 20 (4e), end-of-chapter problem "Articulation points, bridges, and biconnected components": work through the definitions and the low-point idea behind the parts about articulation points and bridges.
- Skip if: you can explain what `low[v]` means and why `low[child] > tin[parent]` identifies a bridge.

## Hints
<details><summary>Hint 1</summary>Run one DFS and record each vertex's discovery time. For each vertex, also track the earliest discovery time you can reach from its subtree using tree edges plus at most one back edge. What does it tell you if a child's subtree cannot get back above the child's parent?</details>
<details><summary>Hint 2</summary>For the bridge test, compare the child's low value with the parent's discovery time (strictly greater vs at least). Which of the two says "this edge is the only link", and which says "this vertex separates the subtree"? And how do you treat the DFS root differently for articulation points?</details>
