# Kth Largest Element in an Array
**Topic:** 09 Sorting and Selection · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Kth Largest Element in an Array" (title kept for cross-reference only)

## Problem
Given `nums` and a 1-indexed `k`, return the `k`-th largest element: the value at position
`k` when the array is ordered from largest to smallest. Duplicates count separately: in
`{5, 5, 4}` the 1st and 2nd largest are both `5` and the 3rd largest is `4`. `1 ≤ k ≤ n`.

Solve it with **quickselect** (see the `quickselect` exercise): partition around a pivot and keep only the side
that holds the answer. The tests cannot enforce this (sorting or a heap also passes the
small cases, and a full sort is fast enough to pass the large case), so using quickselect is
the point of the exercise, not something the tests verify. `nums` may be reordered.

## Examples
- `nums = {3, 2, 1, 5, 6, 4}, k = 2` → `5`
- `nums = {3, 2, 3, 1, 2, 4, 5, 5, 6}, k = 4` → `4` (sorted descending: 6 5 5 4 3 3 2 2 1)
- `nums = {7}, k = 1` → `7`

## Constraints
- 1 ≤ n ≤ 10⁶
- Any `int` value, including `INT_MIN` and `INT_MAX`.
- 1 ≤ k ≤ n

## Target
Time: O(n) expected with quickselect · Space: O(1) extra

## CLRS (optional, ≈15 min)
- §9.2 (3e) / §9.2 (4e), "Selection in expected linear time": RANDOMIZED-SELECT (≈15 min).
- Skip if: you can explain why a random pivot makes the expected work O(n), not O(n log n).

## Hints
<details><summary>Hint 1</summary>The k-th largest is the element at which index of the ascending order? Convert k first, then select.</details>
<details><summary>Hint 2</summary>If a partition sends every element equal to the pivot to one side, what happens on an all-equal array? How can a third "equal" group fix that?</details>
