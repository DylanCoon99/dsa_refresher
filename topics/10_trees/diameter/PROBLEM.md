# Diameter of Binary Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Diameter of Binary Tree" (title kept for cross-reference only)

## Problem
The diameter of a tree is the number of **edges** on the longest path between any two nodes.
The path may or may not pass through the root. A single node (or an empty tree) has diameter `0`.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{1, 2, 3, 4, 5}` → `3` (path 4 → 2 → 1 → 3, or 5 → 2 → 1 → 3)
- `{1, 2}` → `1`
- `{1}` → `0`

## Constraints
- 0 ≤ number of nodes ≤ 2·10⁵ (the largest test is a balanced tree of 2·10⁵ nodes, depth about 18).
- Any `int` values (values do not matter).

## Target
Time: O(n) · Space: O(h)
Recomputing the height of both subtrees at every node costs O(n log n) on a balanced tree and still passes the large test; the test only rules out quadratic work on balanced input.

## Hints
<details><summary>Hint 1</summary>For a fixed node, the longest path that bends at that node uses its left height plus its right height. What do you need to know from each child?</details>
<details><summary>Hint 2</summary>Can the same recursion that returns heights also update a running maximum, so each node is visited once?</details>
