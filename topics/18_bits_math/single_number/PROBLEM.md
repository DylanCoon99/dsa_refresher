# Single Number
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Single Number" (title kept for cross-reference only)

## Problem
In the list `nums`, every value appears exactly twice except one value that appears exactly once.
Return that value. Aim for linear time and no extra memory proportional to `n`.

## Examples
- `nums = {2, 2, 1}` → `1`
- `nums = {4, 1, 2, 1, 2}` → `4`
- `nums = {-7}` → `-7` (a single element is its own answer)

## Constraints
- 1 ≤ n ≤ 3·10⁴ and n is odd
- Any `int` value, including `INT_MIN`
- Exactly one value appears once; every other value appears exactly twice

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>What is x ^ x? What is x ^ 0? Does the order in which you XOR values matter?</details>
<details><summary>Hint 2</summary>If you XOR the whole list together, what happens to each pair?</details>
