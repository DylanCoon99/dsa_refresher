# Two Sum II (Sorted Input)
**Topic:** 03 Two Pointers · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Two Sum II – Input Array Is Sorted" (title kept for cross-reference only)

## Problem
`numbers` is sorted in non-decreasing order. Find the two different positions `i < j` whose
values add up to `target`, and return them as `{i, j}` using **1-based** positions (the first
element is position 1). Exactly one such pair exists. Use only O(1) extra space.

## Examples
- `numbers = {2, 7, 11, 15}, target = 9` → `{1, 2}` (2 + 7 = 9)
- `numbers = {1, 1, 3}, target = 2` → `{1, 2}` (the two 1s are different positions)
- `numbers = {-5, -1, 0, 4}, target = -1` → `{1, 4}`

## Constraints
- 2 ≤ n ≤ 3·10⁵
- −10⁹ ≤ numbers[i] ≤ 10⁹; −2·10⁹ ≤ target ≤ 2·10⁹ (sums fit in a 32-bit `int`, but be careful anyway)
- Sorted ascending; exactly one valid pair

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Start with one pointer at the smallest value and one at the largest. What does their sum tell you?</details>
<details><summary>Hint 2</summary>If the sum is too big, which pointer is the only one that can help by moving, and why can the element it leaves never be part of the answer?</details>
