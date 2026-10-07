# Remove Nth Node From End of List
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Remove Nth Node From End of List" (title kept for cross-reference only)

## Problem
Given the head of a singly linked list and an integer `n`, remove the `n`-th node counted
from the **end** (`n = 1` is the last node) and return the head of the resulting list.
`n` is always between 1 and the list length, inclusive, so the list is never empty.
Removing the head changes which node is returned. You may `delete` nodes you remove; the tests never free nodes, so it makes no difference to them.

## Examples
- `1 → 2 → 3 → 4 → 5`, `n = 2` → `1 → 2 → 3 → 5`
- `1`, `n = 1` → `nullptr`
- `1 → 2`, `n = 2` → `2` (the head is removed)

## Constraints
- 1 ≤ list length ≤ 30 in the tests (invented limit; the O(n) target is independent of it).
- 1 ≤ n ≤ length. Any `int` values.

## Target
Time: O(n), ideally one pass · Space: O(1). The tests cannot tell one pass from two.

## Hints
<details><summary>Hint 1</summary>If you knew the list length L, which node (counting from the front) would you need to stop at? Is a dummy head useful when the removed node is the first one?</details>
<details><summary>Hint 2</summary>Can two pointers kept n nodes apart find that position in a single pass?</details>
