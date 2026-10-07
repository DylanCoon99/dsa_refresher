# Rolling Hash
**Topic:** 21 String Algorithms · **Kind:** Implement · **Difficulty:** Medium

## Problem
Build a `RollingHash` over a fixed string `s`:

- `RollingHash(s)`: preprocess `s` in O(n).
- `hash(pos, len)`: return a 64-bit hash of the substring `s.substr(pos, len)` in O(1). You need `pos + len <= s.size()`; `len` may be `0`.

Use a polynomial hash: treat the characters as digits of a number in some base and reduce modulo a large number (CLRS uses a prime; reducing modulo 2⁶⁴ by letting `std::uint64_t` wrap also works for ordinary inputs). Prefix hashes plus a table of base powers let you get any substring's hash by subtracting and rescaling.

Requirements the tests rely on:

- **Equal substrings hash equal**, wherever they sit in `s` and **across different `RollingHash` objects**. So `hash(pos, len)` must equal `RollingHash(s.substr(pos, len)).hash(0, len)`. In particular the base and modulus must be fixed constants (no per-object randomness), and the value must depend only on the substring's characters.
- **The order of characters matters**: `"ab"` and `"ba"` must hash differently, so a plain sum of characters is not enough.
- **Different substrings of the same length should get different hashes.** A hash cannot promise this for every input, but a decent 64-bit polynomial hash will not collide on the small inputs the tests use. Tests only compare substrings of the *same* length, so you do not need to mix the length into the hash.

## Examples
- `s = "abcabc"` → `hash(0, 3) == hash(3, 3)` (both are `"abc"`)
- `s = "ab"` and `t = "ba"` → `RollingHash(s).hash(0, 2) != RollingHash(t).hash(0, 2)`
- `s = "xyz"` → `hash(1, 2) == RollingHash("yz").hash(0, 2)`

## Constraints
- `0 ≤ |s| ≤ 10⁶`, at most `10⁶` calls to `hash` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary `char` values; map each to a non-zero number (for example its value as `unsigned char`), because with a digit of `0` strings such as `"a"` and `"aa"` can collide.

## Target
Time: O(n) preprocessing, O(1) per query · Space: O(n)

## CLRS (optional, ≈15 min)
- §32.2 (3e) / §32.2 (4e), "The Rabin-Karp algorithm": read the rolling update formula for the hash of the next window. Your class generalises it to arbitrary windows via prefix hashes.
- Skip if: you can explain how to drop the leading character of a window and append a new one in O(1).

## Hints
<details><summary>Hint 1</summary>Define prefix hashes H[i] = H[i-1] * B + s[i-1]. Then H[pos + len] contains the substring's hash shifted left by `len` digits plus everything before it. What must you subtract?</details>
<details><summary>Hint 2</summary>The thing to subtract is H[pos] * B^len, so you need a table of powers of B up to n. With unsigned 64-bit arithmetic that wraps, is the subtraction still correct? (Pick an odd base, and a large random-looking one.)</details>
