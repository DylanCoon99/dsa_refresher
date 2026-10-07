# Swim in Rising Water
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Swim in Rising Water" (title kept for cross-reference only)

## Problem
`grid` is an `n x n` grid whose cell `grid[r][c]` is the elevation of that square; the elevations
are a permutation of `0 .. n*n - 1`. At time `t` the water level is `t`, and you can swim from a
cell to a neighbouring cell (up, down, left or right) only if **both** cells have elevation at
most `t`. You start at the top-left cell and may swim any distance in zero time. Return the
smallest `t` at which you can reach the bottom-right cell.

Because you must be able to stand in the start cell, the answer is at least `grid[0][0]`, and at
least `grid[n-1][n-1]`.

On large grids a recursive DFS can overflow the call stack (under the sanitizer build this shows up
as a CRASH). The large test is a 50 x 50 grid, so prefer an iterative approach. Trying every
route is exponential and will time out.

## Examples
- `{{0,2},{1,3}}` → `3` (the bottom-right cell itself has elevation 3, so you must wait for t = 3)
- `{{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}}` → `16`
- `{{0}}` → `0`

## Constraints
- 1 ≤ n ≤ 50.
- `grid` is a permutation of `0 .. n*n - 1`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n² log n) · Space: O(n²)

## Hints
<details><summary>Hint 1</summary>The water level you need for a route is the highest cell on it. Which of the shortest-path variants from this topic minimizes a route's maximum instead of its sum?</details>
<details><summary>Hint 2</summary>Alternatively: if you raise the level one step at a time and merge each newly flooded cell with its flooded neighbours, when does the start first connect to the end?</details>
