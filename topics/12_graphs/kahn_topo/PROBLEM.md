# Kahn's Topological Sort
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Implement · **Difficulty:** Medium

## Problem
A directed graph has `n` vertices labeled `0 .. n-1` and a list of edges. An edge `{u, v}` means
`u` must come **before** `v`.

```cpp
std::vector<int> topoSortKahn(int n, const std::vector<std::pair<int, int>>& edges);
```

Return a **topological order**: a list containing every vertex exactly once in which every edge
goes forward. If several orders are valid, return any of them (the tests check the property, not a
specific order). If the graph has a cycle (a self-loop counts), no order exists; return an empty
vector. Use Kahn's algorithm: repeatedly remove a vertex that has no remaining incoming edges.

Edges may be repeated, and the graph need not be connected.

## Examples
- `n = 4, edges = {{0,1},{0,2},{1,3},{2,3}}` → `{0, 1, 2, 3}` (or `{0, 2, 1, 3}`)
- `n = 3, edges = {{2,1},{1,0}}` → `{2, 1, 0}` (the only valid order)
- `n = 3, edges = {{0,1},{1,2},{2,0}}` → `{}` (cycle)

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ edges.size() ≤ 10⁵, each endpoint in `[0, n)`; self-loops and repeated edges allowed.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(V + E) · Space: O(V + E)

The large test (a chain of 10⁵ vertices) rejects repeatedly rescanning all edges to find the next
vertex (O(V · E)).

## CLRS (optional, ≈10 min)
- §22.4 (3e) / §20.4 (4e), "Topological sort": the DFS-finish-time version of the algorithm.
  Kahn's algorithm appears there as an end-of-section exercise, so try writing it yourself before
  reading anything about it.
- Skip if: you can explain why a graph has a topological order exactly when it has no cycle.

## Hints
<details><summary>Hint 1</summary>Which vertices can safely be placed first? What do you need to know about each vertex to find them quickly, and how does it change when you place one?</details>
<details><summary>Hint 2</summary>If you run out of vertices with no remaining incoming edges before placing all n, what must be true about the vertices that are left?</details>
