# Kruskal
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement Kruskal's algorithm:

```cpp
long long kruskalMstWeight(int n, std::vector<std::tuple<int,int,int>> edges);
```

The graph is undirected with vertices `0 .. n-1`. Each edge is `{u, v, w}`: an edge between `u` and
`v` of weight `w`. Return the total weight of a minimum spanning tree, or `-1` if the graph is
disconnected (no spanning tree exists). A graph with a single vertex has weight `0`. Weights may be
negative, so `-1` is only ever a sentinel for "disconnected" when the graph really is disconnected;
a connected graph can have a total weight of `-1` or less, and you must return that weight.

The edge list is taken by value, so you may sort it in place. It may contain parallel edges and
self-loops (`u == v`); a self-loop can never be part of a spanning tree.

**Write your UnionFind again inside this header; rewriting it is part of the drill.** Do not
include the Topic 13 header; define the structure (path compression and union by size or rank)
in `kruskal.hpp` yourself.

## Examples
- `n = 4`, edges `{0,1,1}, {1,2,2}, {0,2,3}, {2,3,4}` → `7` (take 1, 2 and 4; the weight-3 edge closes a cycle)
- `n = 4`, edges `{0,1,5}, {2,3,6}` → `-1` (two components)
- `n = 3`, edges `{0,1,-2}, {1,2,-3}, {0,2,1}` → `-5`

## Constraints
- 1 ≤ n ≤ 10⁵; up to 3·10⁵ edges.
- Each weight is an integer in [-10⁹, 10⁹]; the total fits in `long long`.
- Every endpoint is in `[0, n)`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(E log E) · Space: O(V + E)

The large test (10⁵ vertices, 3·10⁵ edges) rejects an O(V²) approach such as Prim with an array scan
(about 10¹⁰ steps).

## CLRS (optional, ≈15 min)
- §23.2 (3e) / §21.2 (4e), "The algorithms of Kruskal and Prim": the Kruskal pseudocode and how it uses the disjoint-set operations (≈15 min). The cut-property theorem (§23.1 / §21.1, ≈10 min) is in the topic README.
- Skip if: you can explain why taking the cheapest edge that joins two different components is safe.

## Hints
<details><summary>Hint 1</summary>Process the edges from lightest to heaviest. When is an edge safe to take, and what structure answers that question quickly?</details>
<details><summary>Hint 2</summary>How many edges does a spanning tree of n vertices have, and what does it mean if you run out of edges before taking that many?</details>
