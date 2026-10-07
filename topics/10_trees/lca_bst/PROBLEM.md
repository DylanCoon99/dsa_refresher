# Lowest Common Ancestor of a BST
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Lowest Common Ancestor of a Binary Search Tree" (title kept for cross-reference only)

## Problem
`root` is a binary search tree with distinct values. `p` and `q` are pointers to nodes that are
**in the tree**. Return a pointer to their lowest common ancestor: the deepest node that has both
`p` and `q` in its subtree, where a node counts as a descendant of itself. So if `p` is an
ancestor of `q`, the answer is `p`; if `p == q`, the answer is that node. The tests compare
the returned pointer with the expected node, not just its value.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
Tree `{6, 2, 8, 0, 4, 7, 9, null, null, 3, 5}`:
- `p = 2`, `q = 8` → node `6`
- `p = 2`, `q = 4` → node `2` (a node is its own descendant)
- `p = 3`, `q = 5` → node `4`

## Constraints
- 1 ≤ number of nodes ≤ 1000 in the tests; values are distinct; `p` and `q` are always nodes of the tree.
- Any `int` values.

## Target
Time: O(h) · Space: O(1) extra if written iteratively

## Hints
<details><summary>Hint 1</summary>Compare `p->val` and `q->val` with the current node's value. If both are smaller, which subtree must contain the answer? If both are larger?</details>
<details><summary>Hint 2</summary>What does it mean for the current node when one target is smaller (or equal) and the other is larger (or equal)?</details>
