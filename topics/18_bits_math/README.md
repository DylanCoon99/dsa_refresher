# 18 · Bit Manipulation and Mathematics
Run everything: `./dsa test 18` · Status: `./dsa list 18`

Overflow is part of this topic. `pow_x_n`'s tests catch negating `INT_MIN` (undefined behavior, which the sanitizer reports as CRASH); `sum_two_integers` only documents the habit of shifting carries in `unsigned`. A correct, standard solution never trips the sanitizer.

## Diagnostic
Attempt cold (≤ 40 min each): `counting_bits`, `sum_two_integers`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Bitwise operators.
- [ ] Two's complement.
- [ ] `x & (x - 1)` (clear the lowest set bit) and `x & -x` (isolate the lowest set bit).
- [ ] Properties of XOR.
- [ ] Enumerating subsets with bitmasks.
- [ ] The GCD via the Euclidean algorithm.
- [ ] Fast modular exponentiation.
- [ ] The Sieve of Eratosthenes.
- [ ] Overflow awareness. This matters especially in C++.

## Implement
- [ ] `fast_pow`: modular exponentiation by squaring · `./dsa test 18/fast_pow`
- [ ] `sieve`: the Sieve of Eratosthenes · `./dsa test 18/sieve`

## Practice
⭐ = interview priority: do these first if you're short on time.
- [ ] `single_number` · Easy · `./dsa test 18/single_number` · ⭐ interview priority
- [ ] `hamming_weight` · Easy · `./dsa test 18/hamming_weight`
- [ ] `counting_bits` · Easy · `./dsa test 18/counting_bits` · ⭐ interview priority
- [ ] `missing_number` · Easy · `./dsa test 18/missing_number`
- [ ] `reverse_bits` · Easy · `./dsa test 18/reverse_bits`
- [ ] `sum_two_integers` · Medium · `./dsa test 18/sum_two_integers`
- [ ] `pow_x_n` · Medium · `./dsa test 18/pow_x_n`
- [ ] `count_primes` · Medium · `./dsa test 18/count_primes`

## CLRS quick reference (≈20 min, all optional)
Bit tricks and the sieve are not covered by CLRS; use the hints in each PROBLEM.md.

| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Review the GCD | §31.2 (3e) / §31.2 (4e), "Greatest common divisor" | The EUCLID procedure and the GCD recursion theorem statement (≈10 min) | You can write Euclid's algorithm from memory and say why gcd(a, b) = gcd(b, a mod b). |
| With `fast_pow` | §31.6 (3e) / §31.6 (4e), "Powers of an element" | The MODULAR-EXPONENTIATION procedure (≈10 min) | You can write square-and-multiply from memory and say why the intermediate values stay below the modulus. |

## Mastery criteria
- [ ] The standard bit tricks can be applied without derivation.
- [ ] Each mathematical routine can be written from memory.
