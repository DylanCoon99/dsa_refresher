# 3Sum
**Topic:** 03 Two Pointers · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "3Sum" (title kept for cross-reference only)

## Problem
Given a list of integers, return every set of three values `{a, b, c}` taken from three
*different positions* that add up to `0`. Each distinct triple of values must appear exactly
once in the result, even if it can be formed from several position choices. The values inside a
triplet and the order of the triplets in the result may be anything.

## Examples
- `nums = {-1, 0, 1, 2, -1, -4}` → `{{-1, -1, 2}, {-1, 0, 1}}`
- `nums = {0, 1, 1}` → `{}` (no triple sums to 0)
- `nums = {0, 0, 0, 0}` → `{{0, 0, 0}}` (reported once)

## Constraints
- 0 ≤ n ≤ 3000
- −10⁵ ≤ nums[i] ≤ 10⁵

## Target
Time: O(n²) · Space: O(1) extra beyond the output (sorting in place is fine)

## Hints
<details><summary>Hint 1</summary>Sort first. Then fix the first value and ask: which two later values add up to its negation?</details>
<details><summary>Hint 2</summary>The inner question is Two Sum II. After you record a triple, how do you skip repeated values so the same triple is not reported twice?</details>
