# Copy List with Random Pointer
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Copy List with Random Pointer" (title kept for cross-reference only)

## Problem
Each `RandomListNode` has `val`, `next`, and `random`; `random` points to any node of the same list
(possibly itself) or is `nullptr`. Build a **deep copy**: a new list of brand-new nodes with the same
values, where every `next` and `random` pointer of the copy points to the corresponding node *of the copy*,
never to an original node. Return the copy's head (`nullptr` for an empty list). The original list must be
left exactly as it was.

## Examples
Written as `{val, index of random target or -1}` per node:
- `{7,-1} {13,0} {11,4} {10,2} {1,0}` → a copy with the same spec; e.g. the copy of node 1 (value 13) has its `random` pointing at the copy of node 0
- `{1,0}` (a node whose random points to itself) → a new node whose `random` is itself
- `nullptr` → `nullptr`

## Constraints
- 0 ≤ number of nodes ≤ 10⁵
- Any `int` values.

## Target
Time: O(n) · Space: O(n) with a hash map, or O(1) extra by interleaving copies with the originals (then you must restore the original)

## Hints
<details><summary>Hint 1</summary>The hard part is "which new node does this random pointer correspond to?". What structure maps old node to new node in O(1)?</details>
<details><summary>Hint 2</summary>Can you create all the copies first, and fill in next and random only once every copy exists?</details>
