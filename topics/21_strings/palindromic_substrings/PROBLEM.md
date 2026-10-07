# Palindromic Substrings
**Topic:** 21 String Algorithms · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Palindromic Substrings" (title kept for cross-reference only)

## Problem
Count the palindromic substrings of `s`. A substring is identified by its start position and length, so two equal substrings at different positions count separately, and every single character counts.

## Examples
- `s = "abc"` → `3`: `"a"`, `"b"`, `"c"`
- `s = "aaa"` → `6`: `"a"` three times, `"aa"` twice, `"aaa"` once
- `s = "abba"` → `6`: `"a"`, `"b"`, `"b"`, `"a"`, `"bb"`, `"abba"`

## Constraints
- `1 ≤ |s| ≤ 5000` (limits chosen for this exercise; the tests stay inside them), so the answer is at most 12 502 500 and fits in `int`. Characters are arbitrary; the tests use lowercase letters.

## Target
Time: O(n²) (O(n) with Manacher's algorithm, optional) · Space: O(1) (or O(n))

## Hints
<details><summary>Hint 1</summary>A palindrome is determined by its center and how far it extends. How many centers does a string of length n have (count the gaps between characters too)?</details>
<details><summary>Hint 2</summary>From a center, every time the two ends still match, you have found one more palindrome. So the number of palindromes at that center equals the number of successful expansions.</details>
