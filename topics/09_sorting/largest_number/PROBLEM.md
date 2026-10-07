# Largest Number
**Topic:** 09 Sorting and Selection · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Largest Number" (title kept for cross-reference only)

## Problem
Given non-negative integers `nums`, arrange them in some order and concatenate their decimal
representations so the resulting number is as large as possible. Return it as a string, since
it can be far too big for any integer type. If the result would be all zeros, return exactly
`"0"` (never `"00"`).

## Examples
- `nums = {10, 2}` → `"210"`
- `nums = {3, 30, 34, 5, 9}` → `"9534330"`
- `nums = {0, 0}` → `"0"`

## Constraints
- 1 ≤ n ≤ 100
- 0 ≤ nums[i] ≤ 10⁹

(These bounds are this exercise's own; the tests stay well inside them.)

## Target
Time: O(n log n · L) where L is the number of digits per value (at most 10) · Space: O(n · L)

## Hints
<details><summary>Hint 1</summary>Sorting the numbers by value, or by plain string comparison, fails on {3, 30}. For two numbers a and b, which of "ab" and "ba" do you want first?</details>
<details><summary>Hint 2</summary>Is "put a before b if a+b > b+a (as strings)" a consistent ordering you can hand to a sort as a comparator? Then, what does the output look like if the first piece is "0"?</details>
