# Binary Search
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Binary Search" (title kept for cross-reference only)

## Problem
`nums` is sorted in strictly increasing order (all values distinct). Return the index of
`target` in `nums`, or `-1` if it is not present.

## Examples
- `nums = {-1, 0, 3, 5, 9, 12}, target = 9` → `4`
- `nums = {-1, 0, 3, 5, 9, 12}, target = 2` → `-1`; 2 is not in the array
- `nums = {5}, target = 5` → `0`

## Constraints
- 1 ≤ n ≤ 10⁶
- −2³¹ ≤ nums[i], target ≤ 2³¹ − 1 (any `int`), values distinct and sorted ascending

## Target
Time: O(log n) · Space: O(1)

## CLRS (optional, ≈5 min)
- §2.3 (3e) / §2.3 (4e), "Designing algorithms": the end-of-section exercise on binary search asks you to describe it and argue its worst case is Θ(lg n).
- Skip if: you can explain why the search range halves each step.

## Hints
<details><summary>Hint 1</summary>If you compare target with the middle element, what can you rule out?</details>
<details><summary>Hint 2</summary>How can you compute the middle index so it cannot overflow, and what guarantees the loop terminates?</details>
