# Kth Smallest Element in a BST
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Kth Smallest Element in a BST" (title kept for cross-reference only)

## Problem
`root` is a valid binary search tree with distinct values. Return the `k`-th smallest value,
counting from `k = 1` for the smallest. `1 ≤ k ≤ n` always holds.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{3, 1, 4, null, 2}`, `k = 1` → `1`
- `{5, 3, 6, 2, 4, null, null, 1}`, `k = 3` → `3`
- `{5, 3, 6, 2, 4, null, null, 1}`, `k = 6` → `6`

## Constraints
- 1 ≤ k ≤ n ≤ 1000 in the tests; values are distinct.
- Any `int` values.

## Target
Time: O(h + k) · Space: O(h)

## Hints
<details><summary>Hint 1</summary>What order do the values come out in during an inorder traversal of a BST?</details>
<details><summary>Hint 2</summary>Do you need the whole traversal, or can you stop after the k-th node? An explicit stack makes stopping early easy.</details>
