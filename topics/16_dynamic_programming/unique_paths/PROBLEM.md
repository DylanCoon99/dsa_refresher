# Unique Paths
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Unique Paths" (title kept for cross-reference only)

## Problem
A robot stands in the top-left cell of an `m`-row by `n`-column grid and wants to reach the bottom-right
cell. Each move goes one cell right or one cell down. Count the distinct paths.

```cpp
int uniquePaths(int m, int n);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `m = 3, n = 7` → `28`
- `m = 3, n = 2` → `3` (right-down-down, down-right-down, down-down-right)
- `m = 1, n = 5` → `1`

## Constraints
- 1 ≤ m, n ≤ 100, and the answer is guaranteed to fit in a 32-bit `int` (so for example 23 × 12 is a valid input; 100 × 100 is not).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(m · n) · Space: O(n) (a single rolling row)

## Hints
<details><summary>Hint 1</summary>A cell can only be entered from above or from the left. What does that say about the number of paths to it in terms of its two neighbours? What are the paths to a cell in the first row or column?</details>
<details><summary>Hint 2</summary>If you fill row by row, which values from the previous row do you still need? Could one array be updated in place?</details>
