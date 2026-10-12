# KMP: Prefix Function and Matcher
**Topic:** 21 String Algorithms · **Kind:** Implement · **Difficulty:** Hard

## Problem
Implement two functions:

- `prefixFunction(s)`: returns a vector `pi` with `pi.size() == s.size()`, where `pi[i]` is the length of the longest **proper** prefix of `s[0..i]` that is also a suffix of `s[0..i]`. ("Proper" means shorter than `s[0..i]` itself, so `pi[0]` is always `0`.)
- `kmpSearch(text, pattern)`: returns every index `i` such that `text` has `pattern` starting at position `i`, in increasing order. Overlapping matches all count. An empty `pattern` returns an empty vector, and so does a pattern longer than the text.

## Examples
- `prefixFunction("aabaaab")` → `{0, 1, 0, 1, 2, 2, 3}`: for example `pi[6] = 3` because `"aab"` is both a prefix and a suffix of the whole string
- `kmpSearch("aaaa", "aa")` → `{0, 1, 2}`: matches overlap
- `kmpSearch("abc", "abcd")` → `{}`: the pattern is longer than the text

## Constraints
- `0 ≤ |s|, |text|, |pattern| ≤ 10⁶` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary `char` values; the tests use lowercase letters.

## Target
Time: O(n + m) · Space: O(m) beyond the output (a full `pi` for the pattern is fine) · Where: n = text length, m = pattern length.

## CLRS (optional, ≈20 min)
- §32.4 (3e) / §32.4 (4e), "The Knuth-Morris-Pratt algorithm": read COMPUTE-PREFIX-FUNCTION and KMP-MATCHER. CLRS indexes from 1 and calls the table π; the exercise is 0-indexed.
- Skip if: you can explain what `pi[i]` means and why the matcher is linear.

## Hints
<details><summary>Hint 1</summary>To extend a border of length k by the next character, you need s[k] to equal it. When it does not, which shorter border should you try next, and where is it stored?</details>
<details><summary>Hint 2</summary>The matcher is the same loop run over `text`, with `pattern` as the string whose table you already built. Why does the running match length never need to move backwards in `text`? (When a full match is found, fall back with `pi[m - 1]` to keep overlaps.)</details>
