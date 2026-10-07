# Search in Rotated Sorted Array
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Search in Rotated Sorted Array" (title kept for cross-reference only)

## Problem
A strictly increasing array of distinct integers was rotated: its last `r` elements
(0 ≤ r < n) were moved to the front, keeping their order. Return the index of `target` in
the rotated array `nums`, or `-1` if it is absent. r = 0 is allowed.

## Examples
- `nums = {4, 5, 6, 7, 0, 1, 2}, target = 0` → `4`
- `nums = {4, 5, 6, 7, 0, 1, 2}, target = 3` → `-1`
- `nums = {1}, target = 0` → `-1`

## Constraints
- 1 ≤ n ≤ 5000
- All values distinct, −10⁴ ≤ nums[i], target ≤ 10⁴

## Target
Time: O(log n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>After you pick mid, at least one of the halves [lo, mid] and [mid, hi] is sorted in the ordinary way. How can you tell which one by comparing two values?</details>
<details><summary>Hint 2</summary>Once you know which half is sorted, can you check in O(1) whether target lies inside it, and so decide which half to keep?</details>
