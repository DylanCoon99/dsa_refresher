# Construct Binary Tree from Preorder and Inorder Traversal
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Construct Binary Tree from Preorder and Inorder Traversal" (title kept for cross-reference only)

## Problem
Given the preorder and inorder traversals of a binary tree whose values are all **distinct**,
rebuild the tree and return its root. The two vectors have the same length and describe the same
tree. Empty vectors give `nullptr`. The tests compare the rebuilt tree with the original using
`to_level_order`.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `preorder = {3, 9, 20, 15, 7}`, `inorder = {9, 3, 15, 20, 7}` → `{3, 9, 20, null, null, 15, 7}`
- `preorder = {1}`, `inorder = {1}` → `{1}`
- `preorder = {1, 2, 3}`, `inorder = {3, 2, 1}` → `{1, 2, null, 3}` (a left-only chain)

## Constraints
- 0 ≤ n ≤ 10⁵ (the largest test is a balanced tree of 10⁵ nodes); values are distinct.
- Any `int` values.

## Target
Time: O(n) with a value → inorder-index lookup · Space: O(n)
Copying a fresh sub-vector at every level, or searching the inorder range linearly for each root, costs about O(n log n) on a balanced tree and still passes the large test. What the test does reject is quadratic behavior on balanced input, such as scanning the whole inorder vector from the start for every node.

## Hints
<details><summary>Hint 1</summary>Which element of the preorder is always the root of the current (sub)tree? Once you know the root, what does its position in the inorder tell you about the left subtree?</details>
<details><summary>Hint 2</summary>Can you avoid slicing vectors by passing index ranges, and avoid searching by looking up each value's inorder index in a hash map built once?</details>
