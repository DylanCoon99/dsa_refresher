# Dijkstra
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement single-source shortest paths for a directed graph with non-negative edge weights:

```cpp
inline constexpr long long kUnreachable = std::numeric_limits<long long>::max();
std::vector<long long> dijkstra(int n, const WeightedGraph& adj, int src);
```

`WeightedGraph` (from `common/graph.hpp`) is `std::vector<std::vector<std::pair<int,int>>>`:
`adj[u]` lists `{v, w}` pairs, one per directed edge `u -> v` of weight `w`. Return a vector of
size `n` where entry `v` is the length of a shortest path from `src` to `v`, and `kUnreachable`
if there is no path. `dist[src]` is `0`.

Use a binary heap (`std::priority_queue`) with **lazy deletion**: push a new entry every time you
improve a distance, and when you pop an entry whose distance is larger than the best known one,
skip it. Path lengths can exceed `INT_MAX`, so use `long long`.

The graph may contain zero-weight edges, parallel edges (same endpoints, different weights),
self-loops, and vertices that cannot be reached.

## Examples
- `n = 4`, edges `0->1 (4), 0->2 (1), 2->1 (2), 1->3 (5)`, `src = 0` → `{0, 3, 1, 8}` (the path to 1 goes through 2)
- `n = 3`, edges `0->1 (7)`, `src = 0` → `{0, 7, kUnreachable}` (vertex 2 has no incoming path)
- `n = 3`, edges `0->1 (1000000000), 1->2 (1000000000), 2->0 (0)`, `src = 0` → `{0, 1000000000, 2000000000}`

## Constraints
- 1 ≤ n ≤ 10⁵; 0 ≤ src < n.
- Up to 3·10⁵ edges; every weight is an integer in [0, 10⁹].
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O((V + E) log V) · Space: O(V + E)

The large test (10⁵ vertices, 3·10⁵ edges) rejects the O(V²) version that scans an array for the
nearest unfinished vertex (about 10¹⁰ steps).

## CLRS (optional, ≈15 min)
- §24.3 (3e) / §22.3 (4e), "Dijkstra's algorithm": the pseudocode and the statement of the correctness theorem (≈15 min). The relaxation background (Ch. 24 intro / Ch. 22 intro, ≈10 min) is in the topic README.
- Skip if: you can explain why a negative edge breaks the greedy finalization.

## Hints
<details><summary>Hint 1</summary>Keep a tentative distance per vertex and a min-heap of <code>{distance, vertex}</code>. Which vertex can you be sure is final when you pop it, and why does that need non-negative weights?</details>
<details><summary>Hint 2</summary>std::priority_queue has no decrease-key. What can you do instead when a shorter path to a vertex is found, and how do you recognise the stale entries when they come out?</details>
