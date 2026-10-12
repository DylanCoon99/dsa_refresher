# Median of Two Sorted Arrays
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Median of Two Sorted Arrays" (title kept for cross-reference only)

## Problem
`nums1` and `nums2` are each sorted in non-decreasing order (duplicates allowed, either may
be empty, not both). Return the median of all `m + n` values combined: the middle value when
`m + n` is odd, or the average of the two middle values when it is even.

The tests only check the answer; they cannot tell O(log(min(m, n))) from O(m + n). Aim for the
logarithmic Target anyway, since that is the point of the exercise.

## Examples
- `nums1 = {1, 3}, nums2 = {2}` → `2.0` (combined 1, 2, 3)
- `nums1 = {1, 2}, nums2 = {3, 4}` → `2.5` (combined 1, 2, 3, 4)
- `nums1 = {}, nums2 = {5}` → `5.0`

## Constraints
- 0 ≤ m, n ≤ 10⁵ and m + n ≥ 1
- Any `int` values, including `INT_MIN` and `INT_MAX`; the sum of two middle values can overflow a 32-bit `int`

## Target
Time: O(log(min(m, n))) · Space: O(1) · Where: m = nums1.size(), n = nums2.size().

## Hints
<details><summary>Hint 1</summary>The median splits the combined values into a left half and a right half of (nearly) equal size, with everything on the left ≤ everything on the right. If you take i elements from nums1 for the left half, how many must come from nums2?</details>
<details><summary>Hint 2</summary>The split is valid when the largest value on each array's left side is ≤ the smallest value on the other array's right side. Can you binary-search i on the shorter array, deciding which way to move from those two comparisons?</details>
