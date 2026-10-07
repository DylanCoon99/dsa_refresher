# Continuous Subarray Sum
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Continuous Subarray Sum" (title kept for cross-reference only)

## Problem
Given a list of non-negative integers `nums` and a positive integer `k`, decide whether some
contiguous subarray of **length at least 2** has a sum that is a multiple of `k`. Zero counts
as a multiple of `k`, so a subarray summing to `0` qualifies. Return `true` if one exists,
`false` otherwise.

## Examples
- `nums = {23, 2, 4, 6, 7}, k = 6` → `true` (`{2, 4}` sums to 6)
- `nums = {23, 2, 6, 4, 7}, k = 6` → `true` (`{23, 2, 6, 4, 7}` sums to 42 = 7 · 6)
- `nums = {23, 2, 6, 4, 7}, k = 13` → `false`

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ nums[i] ≤ 10⁹; the sum of all elements fits in `int`
- 1 ≤ k ≤ 2³¹ − 1

## Target
Time: O(n) · Space: O(min(n, k))

## Hints
<details><summary>Hint 1</summary>If two prefix sums leave the same remainder when divided by k, what can you say about the block between them?</details>
<details><summary>Hint 2</summary>The block must have length at least 2. What should you store in the map for each remainder so that this check is easy, and which remainder is "already seen" before any element is read?</details>
