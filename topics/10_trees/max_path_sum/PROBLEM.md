# Binary Tree Maximum Path Sum
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Binary Tree Maximum Path Sum" (title kept for cross-reference only)

## Problem
A path is a sequence of nodes where each consecutive pair is connected by a parent-child edge,
each node appears at most once, and the path need not pass through the root or end at a leaf. It
contains at least one node. Return the largest sum of node values over all such paths. Values can
be negative: if every value is negative, the answer is the largest single node.

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{1, 2, 3}` → `6` (path 2 → 1 → 3)
- `{-10, 9, 20, null, null, 15, 7}` → `42` (path 15 → 20 → 7, not through the root)
- `{-3}` → `-3`

## Constraints
- 1 ≤ number of nodes ≤ 1000 in the tests.
- Node values in [−1000, 1000], so every path sum fits in `int`.

## Target
Time: O(n) · Space: O(h) · Where: n = number of nodes, h = height of the tree.

## Hints
<details><summary>Hint 1</summary>For a node, what is the best sum of a path that starts at that node and only goes down? Should you ever extend it into a child whose best downward sum is negative?</details>
<details><summary>Hint 2</summary>The best path whose highest node is this one combines the node with up to two downward arms. What does the recursion return to its parent, and what does it only record in a global maximum?</details>
