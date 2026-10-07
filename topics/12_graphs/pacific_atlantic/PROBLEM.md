# Pacific Atlantic Water Flow
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Pacific Atlantic Water Flow" (title kept for cross-reference only)

## Problem
A rectangular island is described by a grid of heights. The **Pacific** touches its top edge and
left edge; the **Atlantic** touches its bottom edge and right edge. Rain on a cell flows to any
4-adjacent cell whose height is **less than or equal to** the current cell's height (so it can
keep flowing across flat ground). A cell on an edge drains directly into the ocean(s) that touch
that edge, so a corner cell can touch two. Return every cell `{row, col}` from which water can
reach **both** oceans. The cells may be returned in any order (the tests sort them before comparing).

## Examples
- `{{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}}` →
  `{{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0}}`
- `{{1}}` → `{{0,0}}`
- A single row `{{3,1,4,1,5}}` → every cell (each one touches the top edge and the bottom edge).

## Constraints
- 1 ≤ rows, cols ≤ 300
- 0 ≤ heights[r][c] ≤ 10⁵
- These limits are chosen for this exercise; they cover every test input. (The large test uses
  heights up to 598.)

## Target
Time: O(rows · cols) · Space: O(rows · cols)

The large test (300 x 300) rejects running a separate search from every cell
(O((rows · cols)²)). On large grids a recursive DFS can also overflow the call stack (under the
sanitizer build this shows up as a CRASH); prefer an iterative BFS or explicit stack.

## Hints
<details><summary>Hint 1</summary>Instead of asking, for every cell, which oceans it reaches, ask which cells each ocean can reach. Where would you start such a search?</details>
<details><summary>Hint 2</summary>If water flows downhill from a cell to the ocean, in which direction does the search from the ocean move, and what changes in the "height" condition?</details>
