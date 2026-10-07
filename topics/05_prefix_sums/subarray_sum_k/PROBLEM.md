# Subarray Sum Equals K
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Subarray Sum Equals K" (title kept for cross-reference only)

## Problem
Given a list of integers `nums` and an integer `k`, count the contiguous, non-empty subarrays
whose elements add up to exactly `k`. Subarrays are counted by position: two subarrays with
the same values at different positions count separately. `nums` may contain negative numbers
and zeros, so a window that only grows or shrinks monotonically will not work.

## Examples
- `nums = {1, 1, 1}, k = 2` → `2` (positions 0..1 and 1..2)
- `nums = {1, 2, 3}, k = 3` → `2` (`{1, 2}` and `{3}`)
- `nums = {1, -1, 0}, k = 0` → `3` (`{1, -1}`, `{0}` and `{1, -1, 0}`)

## Constraints
- 1 ≤ n ≤ 2·10⁴
- −1000 ≤ nums[i] ≤ 1000
- −10⁷ ≤ k ≤ 10⁷

## Target
Time: O(n) · Space: O(n)

The constraints are small enough that an O(n²) scan finishes quickly, so the tests cannot
force O(n). Treat O(n) as the requirement anyway: it is the whole point of the exercise.

## Hints
<details><summary>Hint 1</summary>Let prefix[j] be the sum of the first j elements. A subarray i..j-1 sums to k exactly when which two prefix values differ by k?</details>
<details><summary>Hint 2</summary>As you move right, how many earlier prefixes equal (current prefix − k)? Can a hash map of prefix-sum counts answer that in O(1), and what should it contain before you start?</details>
