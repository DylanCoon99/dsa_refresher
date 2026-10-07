# Sliding Window Maximum
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Sliding Window Maximum" (title kept for cross-reference only)

## Problem
Given an array `nums` and a window size `k`, slide a window of `k` consecutive elements from
the left end of the array to the right end, one position at a time. Return a vector holding
the maximum of the window at each position, in order. The result has `n − k + 1` entries.

## Examples
- `nums = {1, 3, -1, -3, 5, 3, 6, 7}, k = 3` → `{3, 3, 5, 5, 6, 7}`
- `nums = {1}, k = 1` → `{1}`
- `nums = {9, 8, 7, 6}, k = 2` → `{9, 8, 7}`

## Constraints
- 1 ≤ k ≤ n ≤ 10⁵
- −10⁴ ≤ nums[i] ≤ 10⁴

## Target
Time: O(n) · Space: O(k)

## Hints
<details><summary>Hint 1</summary>When a new element arrives, can any earlier element that is smaller than it ever be the maximum of a window again?</details>
<details><summary>Hint 2</summary>Keep a double-ended queue of indices whose values are in decreasing order. What sits at the front, and when must it be removed because it left the window?</details>
