# Word Search
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Word Search" (title kept for cross-reference only)

## Problem
You are given a grid of uppercase letters `board` and a string `word`. Return `true` if `word` can be
spelled by a path through the grid: the path starts at any cell, each next letter is in a cell directly
above, below, left or right of the previous one (no diagonals), and **no cell is used twice** in one path.
Otherwise return `false`.

## Examples
Board `{{A,B,C,E},{S,F,C,S},{A,D,E,E}}`:
- `word = "ABCCED"` → `true`
- `word = "SEE"` → `true`
- `word = "ABCB"` → `false` (the only B next to C is already used by the path)

## Constraints
- 1 ≤ rows, cols ≤ 6 (rows are all the same length)
- 1 ≤ word.size() ≤ 20
- board cells and word letters are uppercase `'A'`–`'Z'`

## Target
Time: O(rows · cols · 3^L) in the worst case, where L = word.size() · Space: O(L) recursion depth

## Hints
<details><summary>Hint 1</summary>Try every cell as the start. From a cell that matches the next letter, what are the up-to-four neighbours you may continue to?</details>
<details><summary>Hint 2</summary>How can you mark a cell as "in use" while exploring it, and what must you do to it when you back out? (The board is passed by value, so you may modify your copy.)</details>
