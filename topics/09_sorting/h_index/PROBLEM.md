# H-Index
**Topic:** 09 Sorting and Selection · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "H-Index" (title kept for cross-reference only)

## Problem
`citations[i]` is the number of citations of researcher's `i`-th paper. The **h-index** is
the largest `h` such that at least `h` of the papers have at least `h` citations each. (The
remaining papers may have any number of citations.) If no `h ≥ 1` works, the answer is `0`.
The input is in no particular order.

## Examples
- `{3, 0, 6, 1, 5}` → `3` (three papers have at least 3 citations: 3, 6, 5)
- `{1, 3, 1}` → `1` (only one paper has at least 2 citations, so `h = 2` fails)
- `{0, 0}` → `0`

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ citations[i] ≤ 10⁹

(These bounds are this exercise's own; the tests stay well inside them.)

## Target
Time: O(n) (counting sort) or O(n log n) (plain sort) · Space: O(n)

## CLRS (optional, ≈10 min)
- §8.2 (3e) / §8.2 (4e), "Counting sort": the counting-array idea (≈10 min).
- Skip if: you can explain why counting occurrences of each key value lets you sort in O(n + k) without comparisons.

## Hints
<details><summary>Hint 1</summary>Sort the citations in descending order. At position i (0-indexed), you know i + 1 papers have at least citations[i] citations. When does that stop being enough?</details>
<details><summary>Hint 2</summary>The answer can never exceed n, so any citation count above n can be treated as n. If you bucket the papers by capped citation count, can you find h with one backward sweep and a running total, with no sort at all (counting sort)?</details>
