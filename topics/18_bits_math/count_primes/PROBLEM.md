# Count Primes
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Count Primes" (title kept for cross-reference only)

## Problem
Return the number of primes **strictly less than** `n`.

## Examples
- `n = 10` → `4` (the primes are 2, 3, 5, 7)
- `n = 2` → `0` (2 is not less than 2)
- `n = 3` → `1` (only 2)

## Constraints
- 0 ≤ n ≤ 1.5·10⁷

## Target
Time: O(n log log n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Testing every number for primality separately is too slow at n = 1.5·10⁷. Can you do the work once for all numbers below n?</details>
<details><summary>Hint 2</summary>When a prime p crosses out its multiples, which multiple is the first one that has not already been crossed out by a smaller prime?</details>
