# Range Sum Query 2D
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Range Sum Query 2D - Immutable" (title kept for cross-reference only)

## Problem
Implement `NumMatrix`, built once from a fixed matrix of integers and then queried many times
for rectangle sums.

- `explicit NumMatrix(const std::vector<std::vector<int>>& matrix)`: preprocess the matrix.
  It is non-empty, rectangular, and never changes afterwards.
- `int sumRegion(int row1, int col1, int row2, int col2) const`: the sum of all entries in
  rows `row1..row2` and columns `col1..col2`. Both corners are inclusive, with
  `row1 <= row2` and `col1 <= col2`, and lie inside the matrix.

Re-derive this from scratch even though you just did prefix_sum_2d; it should take under 5 minutes.

## Examples
Matrix:
```
3 0 1 4 2
5 6 3 2 1
1 2 0 1 5
4 1 0 1 7
1 0 3 0 5
```
- `sumRegion(2, 1, 4, 3)` → `8`
- `sumRegion(1, 1, 2, 2)` → `11`
- `sumRegion(1, 2, 2, 4)` → `12`

## Constraints
- 1 ≤ rows, cols ≤ 200
- −10⁴ ≤ matrix[i][j] ≤ 10⁴ (every region sum fits in `int`)
- up to 10⁵ queries

## Target
Time: O(rows · cols) to build, O(1) per query · Space: O(rows · cols)

## Hints
<details><summary>Hint 1</summary>Let P[i][j] be the sum of the top-left i-by-j block. How do P[i-1][j], P[i][j-1], P[i-1][j-1] and the cell itself combine to give P[i][j]?</details>
<details><summary>Hint 2</summary>The query rectangle is the big corner block minus the strip above it and the strip to its left. Which part did you subtract twice?</details>
