# Partition Around a Pivot
**Topic:** 03 Two Pointers · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement `partitionAround(nums, pivot)`. Rearrange `nums` **in place** so that every value
strictly less than `pivot` comes before every value that is greater than or equal to `pivot`.
Return the number of values less than `pivot`. Apart from that split, the order inside each
side is unspecified. The result must be a permutation of the input. Use O(1) extra space.

This is the partition step of quicksort, here with the pivot given as a value.

## Examples
- `nums = {3, 8, 1, 9, 2}, pivot = 5` → returns `3`; the first three entries are `{3, 1, 2}` in some order, the last two are `{8, 9}` in some order
- `nums = {4, 4, 4}, pivot = 4` → returns `0` (nothing is strictly less)
- `nums = {1, 2, 3}, pivot = 10` → returns `3`

## Constraints
- 0 ≤ n ≤ 10⁵
- −10⁹ ≤ nums[i], pivot ≤ 10⁹

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Keep a boundary index: everything before it is already known to be less than the pivot. Scan the rest once.</details>
<details><summary>Hint 2</summary>When the scanning index finds a value below the pivot, where should it go, and what do you do with the value that was there?</details>
