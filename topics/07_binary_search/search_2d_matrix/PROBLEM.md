# Search a 2D Matrix
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Search a 2D Matrix" (title kept for cross-reference only)

## Problem
`matrix` is an m × n grid of integers (m, n ≥ 1). Each row is sorted in non-decreasing order,
and the first value of every row is strictly greater than the last value of the previous row.
Return `true` if `target` appears anywhere in the grid, else `false`.

## Examples
- `matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, target = 3` → `true`
- same matrix, `target = 13` → `false`; 13 lies between 11 and 16 and is not present
- `matrix = {{4}}, target = 4` → `true`

## Constraints
- 1 ≤ m, n ≤ 100, every row has exactly n entries
- −2³¹ ≤ matrix[i][j], target ≤ 2³¹ − 1 (any `int`)

## Target
Time: O(log(m·n)) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>If you read the grid row by row, left to right, what kind of sequence do you get?</details>
<details><summary>Hint 2</summary>Can you binary-search positions 0 .. m·n−1 and convert a position back to a row and a column with / and %, without building the flat array?</details>
