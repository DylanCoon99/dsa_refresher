# Validate Binary Search Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Validate Binary Search Tree" (title kept for cross-reference only)

## Problem
Return `true` if the tree is a valid binary search tree: for **every** node, all values in its
left subtree are strictly smaller and all values in its right subtree are strictly larger. The
ordering is strict, so duplicate values make a tree invalid (a node equal to its parent, or equal
to any ancestor on the wrong side, is invalid). An empty tree is valid.

Checking each node only against its own parent is not enough: a node deep in a subtree must
respect the bounds set by all of its ancestors. Values can be `INT_MIN` and `INT_MAX`, so
sentinel bounds of those values themselves need care.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{2, 1, 3}` → `true`
- `{5, 1, 4, null, null, 3, 6}` → `false` (3 is in the right subtree of 5 but smaller than 5)
- `{2, 2, 3}` → `false` (a node equal to its parent)

## Constraints
- 0 ≤ number of nodes ≤ 1000 in the tests.
- Any `int` values, including `INT_MIN` (−2147483648) and `INT_MAX` (2147483647).

## Target
Time: O(n) · Space: O(h) · Where: n = number of nodes, h = height of the tree.

## Hints
<details><summary>Hint 1</summary>When you go into a child, what range of values is allowed for the whole subtree there? How does that range shrink as you descend?</details>
<details><summary>Hint 2</summary>If your bounds are plain `int`s, what value would you use for "no lower bound", and does a tree containing `INT_MIN` break it? Could you use optional bounds, wider integers, or pass pointers to the nodes that set the bounds? Alternatively, what does an inorder traversal of a valid BST look like?</details>
