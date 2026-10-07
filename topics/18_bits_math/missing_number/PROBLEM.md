# Missing Number
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Missing Number" (title kept for cross-reference only)

## Problem
`nums` holds `n` distinct integers taken from the range `0..n` (inclusive). Exactly one number of
that range is absent. Return it.

## Examples
- `nums = {3, 0, 1}` → `2`
- `nums = {0, 1}` → `2` (the missing value can be `n` itself)
- `nums = {1}` → `0`

## Constraints
- 1 ≤ n ≤ 10⁴ in the tests; the approach should still work for n up to 10⁵
- All values are distinct and lie in `0..n`

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>If nothing were missing, you would have exactly the numbers 0..n. What is their sum? What is their XOR?</details>
<details><summary>Hint 2</summary>What happens if you XOR every index and every value together, including the index n?</details>
