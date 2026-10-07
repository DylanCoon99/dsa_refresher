# Range Sum Query
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Range Sum Query - Immutable" (title kept for cross-reference only)

## Problem
Implement `NumArray`, built once from a fixed list of integers and then queried many times.

- `explicit NumArray(const std::vector<int>& nums)`: preprocess the list. It is non-empty and
  never changes afterwards.
- `int sumRange(int left, int right) const`: the sum of `nums[left]` through `nums[right]`,
  both ends inclusive, with `0 <= left <= right < n`.

## Examples
`nums = {-2, 0, 3, -5, 2, -1}`
- `sumRange(0, 2)` → `1` (−2 + 0 + 3)
- `sumRange(2, 5)` → `-1` (3 − 5 + 2 − 1)
- `sumRange(0, 5)` → `-3`

## Constraints
- 1 ≤ n ≤ 10⁵
- −10⁴ ≤ nums[i] ≤ 10⁴ (every range sum fits in `int`)
- up to 10⁵ queries

## Target
Time: O(n) to build, O(1) per query · Space: O(n)

## Hints
<details><summary>Hint 1</summary>If you knew the sum of the first k elements for every k, what would the sum of a middle block be?</details>
<details><summary>Hint 2</summary>Can a block sum be written as the difference of two prefix sums? Which two?</details>
