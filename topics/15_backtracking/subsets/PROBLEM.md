# Subsets
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Subsets" (title kept for cross-reference only)

## Problem
Given a list of **distinct** integers `nums`, return every subset of it (the power set), including the
empty subset and the full set. Subsets may be returned in any order, and the order of the elements inside
a subset does not matter. No subset may appear twice.

## Examples
- `nums = {1, 2, 3}` → `{{}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3}}`
- `nums = {0}` → `{{}, {0}}`
- `nums = {}` → `{{}}` (the empty set has exactly one subset, itself)

## Constraints
- 0 ≤ n ≤ 10
- −10 ≤ nums[i] ≤ 10, all distinct

## Target
Time: O(n · 2ⁿ) · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>Each element is either in the subset or not. Can you decide that one element at a time, going left to right?</details>
<details><summary>Hint 2</summary>If you record the current path at every node of the recursion (not only at the leaves), which start index do you pass down so no subset is generated twice?</details>
