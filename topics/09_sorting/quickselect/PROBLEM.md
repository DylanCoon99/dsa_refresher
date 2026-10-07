# Quickselect
**Topic:** 09 Sorting and Selection · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement `int quickselect(std::vector<int>& nums, std::size_t k)`. It returns the element
that would be at index `k` if `nums` were sorted in non-decreasing order, so `k = 0` is the
minimum and `k = n - 1` is the maximum. Duplicates count separately: in `{4, 4, 4}` the
elements at indices 0, 1 and 2 are all `4`. `0 ≤ k < n` always holds.

`nums` may be reordered by the call. Aim for expected O(n) time using the partition idea from
quicksort, discarding the side that cannot contain index `k`. The tests cannot enforce this
(sorting the whole array and returning `nums[k]` also passes the small cases), but the large
test is built to catch a partition that mishandles equal keys.

## Examples
- `nums = {7, 1, 5, 3}, k = 0` → `1`
- `nums = {7, 1, 5, 3}, k = 3` → `7`
- `nums = {2, 2, 9, 2, 5}, k = 2` → `2` (sorted: 2 2 2 5 9)

## Constraints
- 1 ≤ n ≤ 10⁶
- Any `int` value, including `INT_MIN` and `INT_MAX`.

## Target
Time: O(n) expected · Space: O(1) extra

## CLRS (optional, ≈15 min)
- §9.2 (3e) / §9.2 (4e), "Selection in expected linear time": RANDOMIZED-SELECT and the idea behind its expected running time (≈15 min).
- Skip if: you can explain why a random pivot makes the expected work O(n), not O(n log n).

## Hints
<details><summary>Hint 1</summary>After partitioning around a pivot, you know the pivot's final index. If that index is not k, which side can you throw away completely?</details>
<details><summary>Hint 2</summary>What if every element equals the pivot? Does a two-way partition shrink the problem at all? How could a third group "equal to the pivot" let you stop as soon as k lands inside it?</details>
