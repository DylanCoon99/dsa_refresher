# Merge k Sorted Lists
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Merge k Sorted Lists" (title kept for cross-reference only)

## Problem
You get a `std::vector<ListNode*>` of `k` heads, each list sorted in non-decreasing order (an entry may be
`nullptr`; the vector itself may be empty). Return the head of a single sorted list containing every value
from every list, or `nullptr` if there are none. The contents of the vector after the call are unspecified.
You may `delete` nodes you remove; the tests never free nodes, so it makes no difference to them.

Merging the lists one after another into a growing result costs O(N·k) node steps for N total nodes, which the
large test (10⁴ lists of 10 nodes) rejects.

## Examples
- `{1→4→5, 1→3→4, 2→6}` → `1 → 1 → 2 → 3 → 4 → 4 → 5 → 6`
- `{}` → `nullptr`
- `{nullptr}` → `nullptr`

## Constraints
- 0 ≤ k ≤ 10⁴
- 0 ≤ length of each list ≤ 10 (invented limit matching the tests); total nodes ≤ 10⁵
- Any `int` values.

## Target
Time: O(N log k) · Space: O(k) (the tests only reject the O(N·k) approach; they cannot tell a missing log factor)

## CLRS (optional, ≈10 min)
- §6.5 (3e) / §6.5 (4e), "Priority queues": read what a priority queue supports (insert, extract-min) and the heap-based implementation.
- Skip if: you can explain why a heap of k list heads gives the next smallest value in O(log k).

## Hints
<details><summary>Hint 1</summary>At any moment, which values are candidates for the next output node? How many are there?</details>
<details><summary>Hint 2</summary>Which structure returns the smallest of k candidates in O(log k)? Could you instead merge lists in pairs, halving the count each round?</details>
