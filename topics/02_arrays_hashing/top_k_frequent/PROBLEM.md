# Top K Frequent Elements
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Top K Frequent Elements" (title kept for cross-reference only)

## Problem
Given a list of integers `nums` and an integer `k`, return the `k` values that occur most
often in `nums`. The answer is guaranteed to be unique (there is no tie for the k-th place),
and you may return the values in any order.

## Examples
- `nums = {1, 1, 1, 2, 2, 3}, k = 2` → `{1, 2}` (counts 3, 2, 1)
- `nums = {5}, k = 1` → `{5}`
- `nums = {4, 4, 4, 6, 6, 9}, k = 3` → `{4, 6, 9}` (k equals the number of distinct values)

## Constraints
- n ≤ 10⁵
- 1 ≤ k ≤ number of distinct values in `nums`.

## Target
Time: O(n) (counting plus bucket sort by frequency; O(n log k) with a heap is acceptable) · Space: O(n)

## CLRS (optional, ≈15 min)
- §9.2 (3e) / §9.2 (4e), "Selection in expected linear time": read the intro and the RANDOMIZED-SELECT pseudocode.
- Skip if: you know why bucket sort by frequency gives O(n).

## Hints
<details><summary>Hint 1</summary>First count how often each value occurs. What structure maps a value to its count in O(1)?</details>
<details><summary>Hint 2</summary>A count can never exceed n. Could you index buckets by count, and then read the buckets from the highest count downward?</details>
