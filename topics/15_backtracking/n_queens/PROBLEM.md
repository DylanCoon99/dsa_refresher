# N-Queens
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "N-Queens" (title kept for cross-reference only)

## Problem
Place `n` queens on an `n × n` chessboard so that no two queens attack each other: no two share a row, a
column or a diagonal. Return every distinct placement. Each placement is a list of `n` strings of length `n`,
one per row from top to bottom, with `'Q'` for a queen and `'.'` for an empty square. The placements may be
returned in any order. If there is no placement, return an empty list.

## Examples
- `n = 4` → 2 placements: `{".Q..", "...Q", "Q...", "..Q."}` and `{"..Q.", "Q...", "...Q", ".Q.."}`
- `n = 1` → `{{"Q"}}`
- `n = 3` → `{}` (no placement exists)

## Constraints
- 1 ≤ n ≤ 9

## Target
Time: roughly O(n!) with pruning · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>Every row must hold exactly one queen. If you place queens row by row, what does that leave to track?</details>
<details><summary>Hint 2</summary>Which two quantities, computed from (row, col), are constant along a "/" diagonal and along a "\" diagonal? Can you keep a set (or boolean array) for each?</details>
