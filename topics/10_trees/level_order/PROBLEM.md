# Binary Tree Level Order Traversal
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Binary Tree Level Order Traversal" (title kept for cross-reference only)

## Problem
Return the node values grouped by depth: first the root alone, then the root's children from left
to right, then the grandchildren, and so on. Each depth is one inner vector. An empty tree gives an
empty outer vector (not one empty row).

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{3, 9, 20, null, null, 15, 7}` → `{{3}, {9, 20}, {15, 7}}`
- `{1}` → `{{1}}`
- `nullptr` → `{}`

## Constraints
- 0 ≤ number of nodes ≤ 2000 in the tests.
- Any `int` values.

## Target
Time: O(n) · Space: O(w) where w is the maximum width of the tree

## Hints
<details><summary>Hint 1</summary>Which structure visits nodes in the order "all of depth d before any of depth d + 1"?</details>
<details><summary>Hint 2</summary>How can you tell where one level ends and the next begins? What is true about the queue's size at the start of each level?</details>
