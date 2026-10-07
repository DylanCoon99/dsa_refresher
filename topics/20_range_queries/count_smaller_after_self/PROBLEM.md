# Count of Smaller Numbers After Self
**Topic:** 20 Range Query Structures · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Count of Smaller Numbers After Self" (title kept for cross-reference only)

## Problem
Given a list of integers `nums`, return a list `counts` of the same length where `counts[i]` is the number of positions `j > i` with `nums[j] < nums[i]` (strictly smaller; equal values do not count).

## Examples
- `nums = {5, 2, 6, 1}` → `{2, 1, 1, 0}`: after the 5 come 2 and 1 (smaller), after the 2 comes 1, after the 6 comes 1
- `nums = {-1}` → `{0}`
- `nums = {-1, -1}` → `{0, 0}`: equal values are not smaller

## Constraints
- 1 ≤ n ≤ 10⁵ (the large test uses n = 10⁵).
- Any `int` values, including `INT_MIN` and `INT_MAX`, so a Fenwick tree indexed by value needs coordinate compression first.

## Target
Time: O(n log n) · Space: O(n)

## CLRS (optional, ≈15 min)
- §14.1 (3e) / §17.1 (4e), "Dynamic order statistics": read OS-RANK. "How many elements are smaller than x" is the same query on an augmented tree.
- Skip if: you can explain how storing subtree sizes lets a tree answer a rank query in O(log n).

## Hints
<details><summary>Hint 1</summary>Sweep from the right. When you reach `nums[i]`, the only elements you need to count are the ones already swept. What structure counts "how many inserted values are below x" quickly?</details>
<details><summary>Hint 2</summary>Raw values are too spread out to index an array. Can you replace each value by its rank among the sorted distinct values? (A merge sort that counts while merging is a valid alternative.)</details>
