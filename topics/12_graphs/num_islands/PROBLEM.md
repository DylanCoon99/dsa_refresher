# Number of Islands
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Number of Islands" (title kept for cross-reference only)

## Problem
A grid of characters represents a map: `'1'` is land and `'0'` is water. An **island** is a group of
land cells connected up, down, left or right (diagonal neighbors do not connect). Return how many
islands the grid contains. The grid is passed by value, so you may modify your copy.

On large grids a recursive DFS can overflow the call stack (under the sanitizer build this shows up
as a CRASH). The large test is a 300 x 300 grid, so prefer an iterative BFS or an explicit stack.

## Examples
- `{{1,1,1,1,0},{1,1,0,1,0},{1,1,0,0,0},{0,0,0,0,0}}` (as `'1'`/`'0'` characters) → `1`
- `{{1,1,0,0,0},{1,1,0,0,0},{0,0,1,0,0},{0,0,0,1,1}}` → `3`
- `{{1,0},{0,1}}` → `2` (diagonal cells are not connected)

## Constraints
- 1 ≤ rows, cols ≤ 300
- Every cell is `'0'` or `'1'`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(rows · cols) · Space: O(rows · cols)

The large test (300 x 300 all land) rejects starting a fresh search from every land cell
(O((rows · cols)²)).

## Hints
<details><summary>Hint 1</summary>Scan the grid cell by cell. When you meet a land cell, what should happen to the rest of its island so you never count it again?</details>
<details><summary>Hint 2</summary>Treat each land cell as a vertex with up to four neighbors. How many times does the scan need to start a search, compared with the number of land cells?</details>
