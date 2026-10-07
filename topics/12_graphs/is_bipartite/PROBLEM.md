# Is Graph Bipartite?
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Is Graph Bipartite?" (title kept for cross-reference only)

## Problem
An undirected graph is given as adjacency lists: `graph[v]` holds the neighbors of vertex `v`. The
graph is symmetric (`u` is in `graph[v]` exactly when `v` is in `graph[u]`), has no self-loops and
no repeated edges, and **may be disconnected**. It is **bipartite** if its vertices can be split
into two groups so that every edge joins a vertex of one group to a vertex of the other. Return
`true` if it is bipartite and `false` otherwise. Vertices with no edges are allowed.

## Examples
- `{{1,2,3},{0,2},{0,1,3},{0,2}}` → `false` (vertices 0, 1, 2 form a triangle)
- `{{1,3},{0,2},{1,3},{0,2}}` → `true` (groups `{0, 2}` and `{1, 3}`)
- `{{1},{0},{3,4},{2,4},{2,3}}` → `false` (a lone edge plus a triangle)

## Constraints
- 1 ≤ V ≤ 100
- The graph is symmetric with no self-loops and no repeated edges.
- These limits are chosen for this exercise; they cover every test input (the tests use at most 10
  vertices).

## Target
Time: O(V + E) · Space: O(V)

## CLRS (optional, ≈5 min)
- §22.2 (3e) / §20.2 (4e), "Breadth-first search": one of the end-of-section exercises there asks
  for exactly this two-coloring problem. Try it yourself first.
- Skip if: you can explain why a graph is bipartite exactly when it has no odd cycle.

## Hints
<details><summary>Hint 1</summary>Give a vertex a color, then force each neighbor to the opposite color. What does a conflict tell you? Remember that one search from vertex 0 may not reach every component.</details>
<details><summary>Hint 2</summary>When you reach a vertex that already has a color, what should you compare it with, and what does a mismatch or a match mean?</details>
