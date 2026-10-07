# Trapping Rain Water
**Topic:** 03 Two Pointers · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Trapping Rain Water" (title kept for cross-reference only)

## Problem
`height[i]` is the height of a unit-width bar at position `i`. After rain, water collects
between bars. Return the total units of water held. The water above bar `i` has depth
`min(tallest bar at or left of i, tallest bar at or right of i) - height[i]` (never negative).
Water that would run off either end is not counted.

## Examples
- `height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}` → `6`
- `height = {4, 2, 0, 3, 2, 5}` → `9`
- `height = {1, 2, 3}` → `0` (strictly rising, nothing to hold)

## Constraints
- 0 ≤ n ≤ 2·10⁴
- 0 ≤ height[i] ≤ 10⁵

## Target
Time: O(n) · Space: O(1)

An O(n²) per-index scan passes the tests on this exercise, but it is not the target: aim for
a single pass with two pointers.

## Hints
<details><summary>Hint 1</summary>The water above one bar depends only on the tallest bar to its left and the tallest bar to its right. You could precompute both as arrays; can you avoid the arrays?</details>
<details><summary>Hint 2</summary>With pointers at both ends and a running maximum for each side, if the left maximum is smaller than the right maximum, is the left bar's water level already decided?</details>
