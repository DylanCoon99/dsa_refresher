# Longest Consecutive Sequence
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Consecutive Sequence" (title kept for cross-reference only)

## Problem
Given an unsorted list of integers `nums`, return the length of the longest run of values
`x, x+1, x+2, ...` that all occur somewhere in `nums`. The values need not be adjacent in
the list, and duplicates count once. An empty list gives 0.

## Examples
- `nums = {100, 4, 200, 1, 3, 2}` → `4` (the run 1, 2, 3, 4)
- `nums = {1, 2, 2, 3}` → `3` (the duplicate 2 counts once)
- `nums = {}` → `0`

## Constraints
- 0 ≤ n ≤ 10⁵
- Values fit in `int`.

## Target
Time: O(n) expected · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Put every value into a hash set. Which values are the <em>start</em> of a run?</details>
<details><summary>Hint 2</summary>If <code>x - 1</code> is in the set, can <code>x</code> ever start the longest run? If not, from which values do you need to count upward at all?</details>
