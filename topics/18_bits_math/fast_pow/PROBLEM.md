# Fast Exponentiation
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Implement · **Difficulty:** Easy

## Problem
Implement `long long modPow(long long base, long long exp, long long mod)`, which returns
`base^exp mod mod` as a value in `[0, mod)`.

- `exp` may be as large as 10¹⁸, so multiplying `exp` times is far too slow.
- `base` may be negative or at least `mod`; the answer is still the mathematical residue in `[0, mod)`
  (for example `modPow(-2, 3, 5)` is `2`, because `-8 ≡ 2 (mod 5)`).
- `modPow(x, 0, m)` is `1 mod m`, so `modPow(x, 0, 1) == 0` (everything is `0` modulo `1`).
- Every intermediate product must fit in `long long`. Reduce modulo `mod` after each multiplication.

## Examples
- `modPow(2, 10, 1000)` → `24` (2¹⁰ = 1024)
- `modPow(-2, 3, 5)` → `2` (a negative base still gives a non-negative answer)
- `modPow(7, 0, 1)` → `0` (everything is 0 modulo 1)

## Constraints
- 1 ≤ mod ≤ 2·10⁹
- 0 ≤ exp ≤ 10¹⁸
- base is any `long long` with |base| ≤ 10¹⁸ (the tests use far smaller values)

## Target
Time: O(log exp) · Space: O(1)

## CLRS (optional, ≈10 min)
- §31.6 (3e) / §31.6 (4e), "Powers of an element": read the MODULAR-EXPONENTIATION procedure and trace it on a small example.
- Skip if: you can write square-and-multiply from memory and say why the result stays below `mod` after each step.

## Hints
<details><summary>Hint 1</summary>x¹⁰ = (x⁵)². How does knowing the answer for half the exponent help with the full exponent?</details>
<details><summary>Hint 2</summary>Look at the bits of `exp` from lowest to highest: when a bit is set, which factor goes into the result, and what do you do to the base before the next bit?</details>
