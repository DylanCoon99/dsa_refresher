# Eventual Safe States
**Topic:** 22 Advanced Graph Topics · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Find Eventual Safe States" (title kept for cross-reference only)

## Problem
`graph[u]` lists the vertices that `u` has a directed edge to. A vertex is **terminal** if it has no outgoing edges. A vertex is **safe** if every path starting from it reaches a terminal vertex (in particular, a terminal vertex is safe, and no safe vertex can reach a cycle). Return all safe vertices in increasing order.

## Examples
- `{{1,2},{2,3},{5},{0},{5},{},{}}` → `{2,4,5,6}`: vertices 0, 1, 3 lie on or lead into the cycle 0 → 1 → 3 → 0.
- `{{0}}` → `{}`: a self-loop is a cycle.
- `{{1,2},{},{3},{2}}` → `{1}`: vertex 0 has a terminal exit but can also walk into the cycle 2 ↔ 3.

## Constraints
- 0 ≤ n ≤ 10⁴ vertices, total edges ≤ 4·10⁴ (limits chosen for this exercise; the tests stay inside them).
- Self-loops are allowed; there are no repeated edges.
- The reference uses recursive DFS (the largest test has DFS depth about 5·10³); production code would use an explicit stack or Kahn's algorithm.

## Target
Time: O(V + E) · Space: O(V)

## CLRS (optional, ≈10 min)
- §22.3 (3e) / §20.3 (4e), "Depth-first search": read the white / gray / black coloring and why an edge into a gray vertex (a back edge) means a cycle.
- Skip if: you can explain why reaching a gray vertex proves a cycle, and what a black vertex tells you.

## Hints
<details><summary>Hint 1</summary>"Safe" is the opposite of "can reach a cycle". If you already know a vertex's verdict, what does that save when you meet it again from another path?</details>
<details><summary>Hint 2</summary>Could you grow the safe set from the terminal vertices backwards instead? Which vertices become safe once all their outgoing neighbors are safe?</details>
