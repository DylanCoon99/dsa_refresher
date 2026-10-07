# Sieve of Eratosthenes
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Implement · **Difficulty:** Easy

## Problem
Implement `std::vector<int> primesUpTo(int n)`, which returns every prime `p` with `p ≤ n`
(note: `n` itself is included when it is prime), in ascending order. If `n < 2` the result is empty.

## Examples
- `primesUpTo(10)` → `{2, 3, 5, 7}`
- `primesUpTo(2)` → `{2}` (the bound is inclusive)
- `primesUpTo(1)` → `{}`

## Constraints
- 0 ≤ n ≤ 10⁷ (n = 0 and n = 1 are included; the tests use nothing larger than 10⁷)

## Target
Time: O(n log log n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Instead of testing each number for divisibility, what if every prime crossed out its own multiples?</details>
<details><summary>Hint 2</summary>For a prime p, which multiple of p is the first one that no smaller prime has already crossed out? Where does that let the outer loop stop?</details>
