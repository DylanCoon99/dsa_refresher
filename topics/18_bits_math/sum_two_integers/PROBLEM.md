# Sum of Two Integers
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Sum of Two Integers" (title kept for cross-reference only)

## Problem
Return `a + b` for two `int` values **without using the `+` or `-` operators**. (This rule is
stated but not enforced by the tests; the exercise is to build addition out of bitwise operations.)
The true sum always fits in an `int`.

## Examples
- `a = 1, b = 2` → `3`
- `a = -1, b = 1` → `0`
- `a = INT_MAX, b = INT_MIN` → `-1`

## Constraints
- `a` and `b` are `int`, and `a + b` is also within `[INT_MIN, INT_MAX]` (no overflow in the answer)

## Target
Time: O(32) = O(1) · Space: O(1)

A note on shifting: left-shifting a negative signed value was undefined behavior before C++20.
This repo builds as C++20, which defines it (two's complement wrap-around), but doing the carry
shift on `unsigned` values is correct under every standard, so that is the safe habit.

## Hints
<details><summary>Hint 1</summary>Add two bits by hand: which operator gives the sum bit without the carry, and which gives the positions that produce a carry?</details>
<details><summary>Hint 2</summary>The carry belongs one position to the left. If you repeat "sum without carry, carry shifted left" until the carry is zero, when does the loop end for negative numbers in two's complement?</details>
