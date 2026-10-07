# Rotting Oranges
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Rotting Oranges" (title kept for cross-reference only)

## Problem
Each cell of a grid holds `0` (empty), `1` (a fresh orange) or `2` (a rotten orange). Every minute,
each fresh orange that is directly up, down, left or right of a rotten orange becomes rotten, all
at the same time. Return the number of minutes that must pass until no fresh orange remains. If
some fresh orange can never rot, return `-1`. If there are no fresh oranges at the start, the
answer is `0`. The grid is passed by value, so you may modify your copy.

On large grids a recursive DFS can overflow the call stack (under the sanitizer build this shows up
as a CRASH), and DFS does not give shortest times anyway. The large test is 300 x 300; use an
iterative BFS.

## Examples
- `{{2,1,1},{1,1,0},{0,1,1}}` → `4`
- `{{2,1,1},{0,1,1},{1,0,1}}` → `-1` (the orange at the bottom-left is cut off)
- `{{0,2}}` → `0` (no fresh oranges)

## Constraints
- 1 ≤ rows, cols ≤ 300
- Every cell is `0`, `1` or `2`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(rows · cols) · Space: O(rows · cols)

The large test (300 x 300, rotten oranges in the four corners) rejects running a separate search
per fresh orange (O((rows · cols)²)).

## Hints
<details><summary>Hint 1</summary>All rotten oranges spread at the same moment. What does it mean for the starting state of the search that there can be several rotten oranges at time 0?</details>
<details><summary>Hint 2</summary>How do you know when a minute has passed, and how do you decide between "all fresh oranges rotted" and "some never will"?</details>
