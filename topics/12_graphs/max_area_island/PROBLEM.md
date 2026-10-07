# Max Area of Island
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Max Area of Island" (title kept for cross-reference only)

## Problem
A grid of integers represents a map: `1` is land and `0` is water. An **island** is a group of land
cells connected up, down, left or right (not diagonally). The **area** of an island is the number of
cells in it. Return the largest area of any island, or `0` if the grid has no land. The grid is
passed by value, so you may modify your copy.

## Examples
- `{{0,1,1,0},{0,1,0,0},{1,0,0,1}}` → `3`
- `{{0,0,0},{0,0,0}}` → `0`
- `{{1,0},{0,1}}` → `1` (diagonal cells are not connected)

## Constraints
- 1 ≤ rows, cols ≤ 50
- Every cell is `0` or `1`.
- These limits are chosen for this exercise; they cover every test input. There is no large-input
  test, but a recursive DFS can overflow the call stack on much larger grids, so an iterative search
  is the safer habit.

## Target
Time: O(rows · cols) · Space: O(rows · cols)

## Hints
<details><summary>Hint 1</summary>A single traversal of one island can both mark its cells as seen and count them. What do you do with the counts of different islands?</details>
<details><summary>Hint 2</summary>If you start a search from every land cell without remembering visited cells, what goes wrong? What is the cheapest way to remember them?</details>
