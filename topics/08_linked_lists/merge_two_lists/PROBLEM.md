# Merge Two Sorted Lists
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Merge Two Sorted Lists" (title kept for cross-reference only)

## Problem
Given the heads of two singly linked lists, each sorted in non-decreasing order, return the
head of one sorted list holding all their nodes' values. Either input may be `nullptr`. You may
relink the existing nodes or allocate new ones; the tests only check the resulting values.
You may `delete` nodes you remove; the tests never free nodes, so it makes no difference to them.

## Examples
- `1 → 2 → 4` and `1 → 3 → 4` → `1 → 1 → 2 → 3 → 4 → 4`
- `nullptr` and `nullptr` → `nullptr`
- `nullptr` and `0` → `0`

## Constraints
- 0 ≤ length of each list ≤ 200 in the tests (invented limit)
- Any `int` values; each input list is sorted non-decreasing.

## Target
Time: O(n + m) · Space: O(1) extra if you relink nodes (not checked by the tests) · Where: n and m = the lengths of the two lists.

## Hints
<details><summary>Hint 1</summary>Which of the two current heads must come next in the output? Could a dummy head node save you a special case for the first output node?</details>
<details><summary>Hint 2</summary>When one list runs out, what is left of the other?</details>
