# Maximum Depth of Binary Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Maximum Depth of Binary Tree" (title kept for cross-reference only)

## Problem
Return the number of nodes on the longest path from the root down to a leaf. An empty tree has
depth `0`; a single node has depth `1`.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{3, 9, 20, null, null, 15, 7}` → `3`
- `{1, null, 2}` → `2`
- `nullptr` → `0`

## Constraints
- 0 ≤ number of nodes ≤ 1000 in the tests (a 1000-node skewed tree is the deepest case).
- Any `int` values.

## Target
Time: O(n) · Space: O(h) · Where: n = number of nodes, h = height of the tree.

## Hints
<details><summary>Hint 1</summary>How does the depth of a tree relate to the depths of its two subtrees?</details>
<details><summary>Hint 2</summary>What is the depth of an empty subtree, and does choosing that base case let you avoid a special case for leaves?</details>
