# Combination Sum II
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Combination Sum II" (title kept for cross-reference only)

## Problem
Given a list of positive integers `candidates` that **may contain repeated values**, and a positive integer
`target`, return every distinct combination of candidates that sums to `target`. Each element of the list
(each position) may be used **at most once**. Two combinations are the same if they use each value the same
number of times, so a repeated value must not produce the same combination twice. Return the combinations in
any order, with any order inside each. If there is none, return an empty list.

## Examples
- `candidates = {10, 1, 2, 7, 6, 1, 5}, target = 8` → `{{1,1,6}, {1,2,5}, {1,7}, {2,6}}`
- `candidates = {2, 5, 2, 1, 2}, target = 5` → `{{1,2,2}, {5}}`
- `candidates = {1, 1, 1, 1}, target = 2` → `{{1,1}}` (four ways to pick two 1s, but only one combination)

## Constraints
- 1 ≤ n ≤ 100
- 1 ≤ candidates[i] ≤ 50
- 1 ≤ target ≤ 100

## Target
Time: exponential in the worst case, but proportional to the work for *distinct* combinations: with the duplicate skip, 100 equal values and target 30 must finish instantly · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>Sort the candidates first. What does that let you say about equal values?</details>
<details><summary>Hint 2</summary>At one recursion level, once you have tried a value as the next pick, why is trying an equal value again at the same level pointless?</details>
