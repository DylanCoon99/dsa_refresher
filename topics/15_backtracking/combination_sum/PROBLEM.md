# Combination Sum
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Combination Sum" (title kept for cross-reference only)

## Problem
Given a list of **distinct** positive integers `candidates` and a positive integer `target`, return every
distinct combination of candidates that sums to `target`. Each candidate may be used **any number of times**.
Two combinations are the same if they use each value the same number of times, so `{2, 3}` and `{3, 2}` are
one combination. Return the combinations in any order, with any order inside each. If there is none,
return an empty list.

## Examples
- `candidates = {2, 3, 6, 7}, target = 7` → `{{2,2,3}, {7}}`
- `candidates = {2, 3, 5}, target = 8` → `{{2,2,2,2}, {2,3,3}, {3,5}}`
- `candidates = {5, 6}, target = 3` → `{}` (every candidate is larger than the target)

## Constraints
- 1 ≤ n ≤ 8
- 1 ≤ candidates[i] ≤ 40, all distinct
- 1 ≤ target ≤ 40

## Target
Time: exponential in target / min(candidates) (output-sensitive; pruning keeps it to the actual combinations explored) · Space: O(target / min(candidates)) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>To avoid {2,3} and {3,2} both appearing, can you only ever pick candidates in non-decreasing index order?</details>
<details><summary>Hint 2</summary>When you pick candidate i, which index do you recurse from: i or i + 1? What does that say about reuse?</details>
