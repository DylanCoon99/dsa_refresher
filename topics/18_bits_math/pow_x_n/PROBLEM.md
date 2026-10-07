# Pow(x, n)
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Pow(x, n)" (title kept for cross-reference only)

## Problem
Compute `x` raised to the integer power `n` and return it as a `double`. `n` may be negative
(`x^-k` is `1 / x^k`) and may be any `int`, including `INT_MIN`.

Beware: `-n` overflows `int` when `n == INT_MIN`. Widen to `long long` before negating.

## Examples
- `x = 2.0, n = 10` → `1024.0`
- `x = 2.0, n = -2` → `0.25`
- `x = 5.0, n = 0` → `1.0`

## Constraints
- `n` is any `int`, including `INT_MIN` and `INT_MAX`
- When `n < 0`, `x ≠ 0`
- Tests only use inputs whose exact result is representable as a finite `double` or underflows to `0.0`
  (the tests compare against `std::pow` with 1e-9 relative error only for |n| ≤ 10³; for larger |n|
  they use bases such as ±1 where the answer is exact, or a looser tolerance, because repeated
  squaring accumulates rounding error)

## Target
Time: O(log |n|) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>x¹⁰ = (x⁵)². What is the cost if you can always halve the exponent?</details>
<details><summary>Hint 2</summary>For a negative exponent, which value do you raise to which positive power? What is the value of `-n` when `n` is the smallest `int`, and which type avoids that?</details>
