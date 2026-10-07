# Dedup Sorted Array
**Topic:** 03 Two Pointers · **Kind:** Implement · **Difficulty:** Easy

## Problem
Implement `removeDuplicates(nums)`. `nums` is sorted in non-decreasing order. Rearrange it
**in place** so that its first `k` entries are the distinct values, each once and in their
original order, and return `k`. What is stored after position `k` is unspecified, and the
vector's size need not change. Do not allocate a second array.

## Examples
- `nums = {1, 1, 2}` → returns `2`; first two entries are `{1, 2}`
- `nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}` → returns `5`; first five entries are `{0, 1, 2, 3, 4}`
- `nums = {}` → returns `0`

## Constraints
- 0 ≤ n ≤ 3·10⁴
- Sorted ascending (non-decreasing); −10⁴ ≤ nums[i] ≤ 10⁴

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Use two indices that both move left to right: one reads every element, one marks where the next kept value goes.</details>
<details><summary>Hint 2</summary>Since the input is sorted, how can you tell that the element you are reading is new, using only the last element you kept?</details>
