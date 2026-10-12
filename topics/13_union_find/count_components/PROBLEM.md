# Count Components
**Topic:** 13 Union-Find (Disjoint Sets) · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Number of Connected Components in an Undirected Graph" (title kept for cross-reference only)

## Problem
An undirected graph has `n` nodes numbered `0 .. n-1` and a list of edges, each edge `{u, v}` joining
two nodes. Return the number of connected components, where an isolated node is a component of its
own. The same edge may appear more than once, in either orientation.

## Examples
- `n = 5, {{0,1},{1,2},{3,4}}` → `2` (`{0,1,2}` and `{3,4}`)
- `n = 4, {}` → `4` (no edges, every node alone)
- `n = 3, {{0,1},{1,0},{0,1}}` → `2` (repeats change nothing; node 2 is alone)

## Constraints
- 1 ≤ n ≤ 2000
- 0 ≤ edges.size() ≤ 5000, each edge has exactly two nodes in `[0, n)`, and the two are different.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O((n + E) · α(n)) · Space: O(n) · Where: E = number of edges.

## Hints
<details><summary>Hint 1</summary>Start with n separate groups. What happens to the number of groups each time an edge joins two nodes that are in different groups, and what if they are already in the same group?</details>
<details><summary>Hint 2</summary>Which structure answers "are these two nodes already together?" and merges two groups cheaply?</details>
