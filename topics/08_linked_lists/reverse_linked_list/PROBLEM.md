# Reverse Linked List
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Reverse Linked List" (title kept for cross-reference only)

## Problem
Given the head of a singly linked list, reverse the list and return the new head (the old
last node). An empty list (`nullptr`) reverses to `nullptr`. You may `delete` nodes you remove; the tests never free nodes, so it makes no difference to them.

Know the **iterative** form: a recursive version uses one stack frame per node, and with 10⁶
nodes in a Debug+ASan build that overflows the stack and the test reports CRASH.

## Examples
- `1 → 2 → 3 → 4 → 5` → `5 → 4 → 3 → 2 → 1`
- `1 → 2` → `2 → 1`
- `nullptr` → `nullptr`

## Constraints
- 0 ≤ number of nodes ≤ 10⁶
- Any `int` values.

## Target
Time: O(n) · Space: O(1) (the tests cannot measure extra space; they only reject deep recursion at 10⁶ nodes)

## Hints
<details><summary>Hint 1</summary>While walking the list, what must you remember before you overwrite a node's next pointer?</details>
<details><summary>Hint 2</summary>Can you keep two pointers, "the reversed part so far" and "the rest", and move one node from the second to the first each step?</details>
