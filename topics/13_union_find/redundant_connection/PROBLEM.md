# Redundant Connection
**Topic:** 13 Union-Find (Disjoint Sets) · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Redundant Connection" (title kept for cross-reference only)

## Problem
A connected undirected graph with `n` nodes labelled `1 .. n` started as a tree and then had one extra
edge added, so `edges` holds exactly `n` edges. Return an edge that can be removed so the remaining
`n - 1` edges form a tree. If several edges qualify, return the one that appears **last** in `edges`.
The result is the edge exactly as listed in the input (same orientation).

## Examples
- `{{1,2},{1,3},{2,3}}` → `{2,3}` (the triangle; removing any edge works, so the last one is returned)
- `{{1,2},{2,3},{3,4},{1,4},{1,5}}` → `{1,4}` (the cycle is 1-2-3-4; `{1,4}` is its last edge in the list)
- `{{1,2},{1,3},{3,2},{4,1}}` → `{3,2}` (the cycle edge sits in the middle; the later cycle edge wins)

## Constraints
- 3 ≤ n ≤ 1000, and `edges.size() == n`.
- Every edge is `{a, b}` with `1 ≤ a, b ≤ n` and `a != b`; no edge is listed twice (in either orientation).
- Removing exactly one edge leaves a tree; equivalently the graph is connected and has exactly one cycle.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n · α(n)) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Process the edges in order, keeping track of which nodes are already connected. What does it tell you when an edge joins two nodes that are already connected?</details>
<details><summary>Hint 2</summary>The first edge that closes a cycle while you scan left to right: is it the last edge of that cycle in the input? Why does that matter for the "last in input" rule?</details>
