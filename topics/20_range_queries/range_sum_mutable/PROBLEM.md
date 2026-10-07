# Range Sum Query, Mutable
**Topic:** 20 Range Query Structures · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Range Sum Query - Mutable" (title kept for cross-reference only)

## Problem
Design a `NumArray` built from a list of integers `nums`:

- `update(index, val)`: set `nums[index]` to `val` (replace, not add).
- `sumRange(left, right)`: return the sum of `nums[left..right]` inclusive, with `left <= right`.

Calls to the two methods are interleaved arbitrarily. A prefix-sum array answers `sumRange` in O(1) but rebuilding it on every update costs O(n) per update, which is O(n²) overall on the large test. Pick a structure where both operations are O(log n).

## Examples
- `nums = {1, 3, 5}`: `sumRange(0, 2)` → `9`
- then `update(1, 2)`: `sumRange(0, 2)` → `8`
- `nums = {4}`: `sumRange(0, 0)` → `4`

## Constraints
- 1 ≤ n ≤ 10⁵; at most 10⁵ calls per test (the large test uses n = 10⁵).
- |nums[i]|, |val| ≤ 10⁴, so every sum fits in `int`.

## Target
Time: O(n) build, O(log n) per call · Space: O(n)

## Hints
<details><summary>Hint 1</summary>You need prefix-like sums that survive point changes. Which structure from this topic updates one position and answers prefix queries, both in O(log n)?</details>
<details><summary>Hint 2</summary>An `update` is an assignment. If the structure only supports "add delta", what delta do you pass?</details>
