# Subsets II
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Subsets II" (title kept for cross-reference only)

## Problem
Given a list of integers `nums` that **may contain repeated values**, return every distinct subset.
Two subsets are the same if they contain the same values with the same multiplicities, regardless of
which positions the values came from. Subsets may be returned in any order, and the order of the
elements inside a subset does not matter. No subset may appear twice.

## Examples
- `nums = {1, 2, 2}` → `{{}, {1}, {2}, {1,2}, {2,2}, {1,2,2}}`
- `nums = {2, 2, 2}` → `{{}, {2}, {2,2}, {2,2,2}}` (4 subsets)
- `nums = {0}` → `{{}, {0}}`

## Constraints
- 0 ≤ n ≤ 10
- −10 ≤ nums[i] ≤ 10

## Target
Time: O(n · 2ⁿ) · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>If equal values sit next to each other, which copy of a value can you pick first? Is it ever useful to pick the second copy without the first?</details>
<details><summary>Hint 2</summary>After sorting, at a given recursion level, when should you skip a candidate because it equals the one you just tried at that same level?</details>
