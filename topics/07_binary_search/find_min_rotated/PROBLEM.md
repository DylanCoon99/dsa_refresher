# Find Minimum in Rotated Sorted Array
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Find Minimum in Rotated Sorted Array" (title kept for cross-reference only)

## Problem
A strictly increasing array of distinct integers was rotated: its last `r` elements
(0 ≤ r < n) were moved to the front, keeping their order. Return the smallest element of
`nums`. The case r = 0 (not rotated) is allowed.

## Examples
- `nums = {3, 4, 5, 1, 2}` → `1`
- `nums = {4, 5, 6, 7, 0, 1, 2}` → `0`
- `nums = {11, 13, 15, 17}` → `11`; not rotated, the minimum is the first element

## Constraints
- 1 ≤ n ≤ 5000
- All values distinct, −5000 ≤ nums[i] ≤ 5000

## Target
Time: O(log n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Compare nums[mid] with the last element nums[hi]. Which side of mid can the minimum be on in each case?</details>
<details><summary>Hint 2</summary>If nums[mid] is smaller than nums[hi], could mid itself be the minimum? So should you set hi = mid or hi = mid − 1?</details>
