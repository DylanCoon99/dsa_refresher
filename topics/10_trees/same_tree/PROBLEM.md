# Same Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Same Tree" (title kept for cross-reference only)

## Problem
Return `true` if the two trees have exactly the same shape and the same value at every
corresponding position, `false` otherwise. Two empty trees are the same; an empty tree and a
non-empty tree are not.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{1, 2, 3}` and `{1, 2, 3}` → `true`
- `{1, 2}` and `{1, null, 2}` → `false` (same values, different shape)
- `nullptr` and `nullptr` → `true`

## Constraints
- 0 ≤ number of nodes ≤ 1000 in the tests, for each tree.
- Any `int` values.

## Target
Time: O(min(n, m)) · Space: O(h) · Where: n and m = the node counts of the two trees, h = height of the shorter tree.

## Hints
<details><summary>Hint 1</summary>When are two single positions "equal"? Consider the cases: both empty, exactly one empty, both present.</details>
<details><summary>Hint 2</summary>If both nodes are present and their values match, what else must be true about their children?</details>
