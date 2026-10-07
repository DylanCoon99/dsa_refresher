# Permutations
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Permutations" (title kept for cross-reference only)

## Problem
Given a list of **distinct** integers `nums`, return every ordering of its elements. The permutations may be
returned in any order; the order of the elements inside each permutation is what makes it distinct. No
permutation may appear twice.

## Examples
- `nums = {1, 2, 3}` → `{{1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}}`
- `nums = {0, 1}` → `{{0,1}, {1,0}}`
- `nums = {1}` → `{{1}}`

## Constraints
- 1 ≤ n ≤ 6
- −10 ≤ nums[i] ≤ 10, all distinct

## Target
Time: O(n · n!) · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>Build the permutation one position at a time. What do you need to track so you never reuse an element?</details>
<details><summary>Hint 2</summary>Instead of a "used" array, could you swap each remaining element into the current position and swap it back afterwards?</details>
