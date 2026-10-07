# Contains Duplicate
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Contains Duplicate" (title kept for cross-reference only)

## Problem
Given a list of integers `nums`, return `true` if some value appears at least twice, and
`false` if every value is distinct.

## Examples
- `nums = {1, 2, 3, 1}` → `true` (1 appears twice)
- `nums = {1, 2, 3, 4}` → `false`
- `nums = {7}` → `false` (a single element cannot repeat)

## Constraints
- 1 ≤ n ≤ 10⁵
- Values fit in `int`.

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>While scanning left to right, what do you need to remember about the elements already passed?</details>
<details><summary>Hint 2</summary>Can a set tell you in O(1) whether the current value has been seen before?</details>
