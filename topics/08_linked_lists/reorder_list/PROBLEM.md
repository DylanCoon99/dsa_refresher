# Reorder List
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Reorder List" (title kept for cross-reference only)

## Problem
Given the head of a singly linked list `L0 → L1 → … → Ln`, rearrange it **in place** into
`L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …`. Do not change any node's value and do not allocate
new nodes: the tests check that the very same node objects appear in the new order, and that
the last node's `next` is `nullptr`. The head node stays the head. The function returns nothing.

## Examples
- `1 → 2 → 3 → 4` → `1 → 4 → 2 → 3`
- `1 → 2 → 3 → 4 → 5` → `1 → 5 → 2 → 4 → 3`
- `nullptr` or a single node → unchanged

## Constraints
- 0 ≤ number of nodes ≤ 50 in the tests. This limit is invented to keep the exhaustive checks small; the O(n) target is independent of it.
- Any `int` values.

## Target
Time: O(n) · Space: O(1) extra (not measurable by the tests)

## Hints
<details><summary>Hint 1</summary>The output alternates between the front half and the back half read backwards. How do you find the middle node, and how do you read the second half backwards?</details>
<details><summary>Hint 2</summary>Split at the middle, reverse the second half, then weave the two halves together. What must the final node's next become?</details>
