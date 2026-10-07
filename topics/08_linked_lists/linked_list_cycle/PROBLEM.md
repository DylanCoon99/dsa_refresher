# Linked List Cycle
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Linked List Cycle" (title kept for cross-reference only)

## Problem
Given the head of a singly linked list, return `true` if some node can be reached again by
following `next` pointers (the list has a cycle), and `false` if the list ends at `nullptr`.
An empty list has no cycle. Do not modify the list.

The target is **O(1) extra memory** (Floyd's slow/fast pointers). The tests cannot measure
memory, so a hash-set solution also passes; use the pointer technique anyway, it is the point of the exercise.

## Examples
- `3 → 2 → 0 → -4` with the tail linked back to the node at index 1 → `true`
- `1 → 2` with the tail linked back to index 0 → `true`
- `1` with no cycle → `false`

## Constraints
- 0 ≤ number of nodes ≤ 10⁶
- Any `int` values.

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>If two runners move along the list at different speeds, what happens to the faster one on a list with no cycle? And on a list with one?</details>
<details><summary>Hint 2</summary>Inside a cycle, the gap between the runners changes by one each step. Why must it eventually hit zero?</details>
