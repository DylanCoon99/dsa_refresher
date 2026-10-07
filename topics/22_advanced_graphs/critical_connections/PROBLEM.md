# Critical Connections
**Topic:** 22 Advanced Graph Topics · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Critical Connections in a Network" (title kept for cross-reference only)

## Problem
There are `n` servers numbered `0..n-1`, joined by undirected cables; `connections[i] = {a, b}` is one cable. Every server can reach every other. A cable is **critical** if removing it leaves some pair of servers unable to reach each other.

Return all critical cables, each as a two-element vector, in any order and with the two endpoints in either order.

## Examples
- `n = 4`, `{{0,1},{1,2},{2,0},{1,3}}` → `{{1,3}}`: the triangle survives losing any one edge; the tail edge does not.
- `n = 4`, `{{0,1},{1,2},{2,3}}` → all three edges: a path is all critical.
- `n = 3`, `{{0,1},{1,2},{2,0}}` → `{}`.

## Constraints
- 2 ≤ n ≤ 2·10⁴; `n - 1 ≤ connections.size() ≤ 6·10⁴` (limits chosen for this exercise; the largest test uses exactly these).
- The graph is connected, with no self-loops and no repeated cables.
- The reference uses recursive DFS (the largest test has DFS depth up to roughly 10⁴); production code would use an explicit stack.

## Target
Time: O(V + E) · Space: O(V + E)

## Hints
<details><summary>Hint 1</summary>A cable lying on a cycle is never critical. How could one DFS tell you, for each tree edge, whether some back edge jumps over it?</details>
<details><summary>Hint 2</summary>Track each vertex's discovery time and the smallest discovery time reachable from its subtree. When is a tree edge from p to c the only way back to p's side?</details>
