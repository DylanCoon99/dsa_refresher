# Min Effort Path
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Path With Minimum Effort" (title kept for cross-reference only)

## Problem
`heights` is a grid of integers. You start at the top-left cell and want to reach the bottom-right
cell, moving one step up, down, left or right at a time. The **effort** of a route is the largest
absolute height difference between two consecutive cells on it. Return the smallest effort over
all routes. For a 1 x 1 grid the answer is `0`.

On large grids a recursive DFS can overflow the call stack (under the sanitizer build this shows up
as a CRASH). The large test is a 100 x 100 grid, so prefer an iterative approach. Trying every
route is exponential and will time out.

## Examples
- `{{1,2,2},{3,8,2},{5,3,5}}` → `2` (the route 1 → 3 → 5 → 3 → 5 down the left column and along the bottom row has every step of size 2)
- `{{1,2,3},{3,8,4},{5,3,5}}` → `1` (route 1 → 2 → 3 → 4 → 5 has every step of size 1)
- `{{7}}` → `0`

## Constraints
- 1 ≤ rows, cols ≤ 100.
- 1 ≤ heights[r][c] ≤ 10⁶.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(R · C · log(R · C)) · Space: O(R · C)

## Hints
<details><summary>Hint 1</summary>Minimizing the <em>largest</em> step is a shortest-path problem where a route's cost is a maximum instead of a sum. What goes in the heap, and how do you combine the cost so far with the next step?</details>
<details><summary>Hint 2</summary>Alternatively: if someone fixes a maximum allowed step E, how can you check in linear time whether the target is reachable? What can you do with that yes/no answer across all values of E?</details>
