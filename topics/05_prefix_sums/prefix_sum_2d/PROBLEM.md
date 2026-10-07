# 2-D Prefix Sum
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement `PrefixSum2D`, a structure built once from a fixed rectangular grid of integers
and then queried many times for the sum of a sub-rectangle.

- `explicit PrefixSum2D(const std::vector<std::vector<int>>& grid)`: preprocess the grid.
  The grid is non-empty and rectangular (every row has the same length). It is not modified
  afterwards.
- `long long sumRegion(int r1, int c1, int r2, int c2) const`: the sum of `grid[r][c]` over
  all `r1 <= r <= r2` and `c1 <= c <= c2`. Both corners are inclusive, with `r1 <= r2` and
  `c1 <= c2`, and they lie inside the grid.

The result is a `long long` because the total of many large `int` values can exceed the
range of `int`.

## Examples
Grid:
```
3 0 1 4 2
5 6 3 2 1
1 2 0 1 5
4 1 0 1 7
1 0 3 0 5
```
- `sumRegion(2, 1, 4, 3)` → `8` (rows 2–4, columns 1–3)
- `sumRegion(1, 1, 2, 2)` → `11`
- `sumRegion(1, 2, 2, 4)` → `12`

## Constraints
- 1 ≤ rows, cols ≤ 1000
- −10⁹ ≤ grid[r][c] ≤ 10⁹ (so a region sum can exceed the `int` range)
- up to 10⁵ queries

## Target
Time: O(rows · cols) to build, O(1) per query · Space: O(rows · cols)

## Hints
<details><summary>Hint 1</summary>Define P[i][j] as the sum of the whole rectangle from the top-left corner to (i-1, j-1). How could you fill P with one pass over the grid?</details>
<details><summary>Hint 2</summary>A query rectangle is a big corner rectangle minus two strips. What happens to the overlap of the two strips, and how do you correct for it?</details>
