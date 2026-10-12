# Subtree of Another Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Subtree of Another Tree" (title kept for cross-reference only)

## Problem
Return `true` if some node of `root` has a subtree identical to `subRoot`: same shape and
same values, and covering **everything** below that node (the matching node must have no extra
descendants beyond those in `subRoot`). Values may repeat, so finding a node with the right value
is not enough.

Both trees are non-empty (at least one node each).

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `root = {3, 4, 5, 1, 2}`, `subRoot = {4, 1, 2}` → `true`
- `root = {3, 4, 5, 1, 2, null, null, null, null, 0}`, `subRoot = {4, 1, 2}` → `false` (the node 2 has an extra child 0 in root)
- `root = {1, 1}`, `subRoot = {1}` → `true`

## Constraints
- 1 ≤ nodes in `root` ≤ 2000 and 1 ≤ nodes in `subRoot` ≤ 1000 in the tests.
- Any `int` values.

## Target
Time: O(n · m) simple approach (n and m the node counts) · Space: O(h) · Where: h = height of the main tree.

## Hints
<details><summary>Hint 1</summary>You already know how to test whether two trees are identical. At which nodes of `root` do you need to run that test?</details>
<details><summary>Hint 2</summary>If the first node with a matching value does not give an identical tree, can a later node with the same value still match?</details>
