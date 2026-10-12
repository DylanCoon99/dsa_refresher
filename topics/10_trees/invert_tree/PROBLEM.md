# Invert Binary Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Invert Binary Tree" (title kept for cross-reference only)

## Problem
Mirror a binary tree: at every node, swap the left and right subtrees. Return the root of the
mirrored tree (the same root node, or `nullptr` for an empty tree). The tests compare the result
by shape and values, so modifying the nodes in place or building new ones both pass.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{4, 2, 7, 1, 3, 6, 9}` → `{4, 7, 2, 9, 6, 3, 1}`
- `{1, 2}` → `{1, null, 2}`
- `nullptr` → `nullptr`

## Constraints
- 0 ≤ number of nodes ≤ 1000 in the tests (recursion depth is not an issue at this size).
- Any `int` values.

## Target
Time: O(n) · Space: O(h) · Where: n = number of nodes, h = height of the tree.

## Hints
<details><summary>Hint 1</summary>If you could already mirror both children's subtrees, what is left to do at the current node?</details>
<details><summary>Hint 2</summary>Do the swap before or after the recursive calls: does the order matter for the result?</details>
