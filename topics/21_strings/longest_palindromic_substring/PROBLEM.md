# Longest Palindromic Substring
**Topic:** 21 String Algorithms · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Palindromic Substring" (title kept for cross-reference only)

## Problem
Return a longest contiguous substring of `s` that is a palindrome (reads the same forwards and backwards). If several substrings tie for the longest length, return any one of them; the tests check that your answer is a substring, is a palindrome, and has the maximum length.

## Examples
- `s = "babad"` → `"bab"` (or `"aba"`): both have length 3
- `s = "cbbd"` → `"bb"`: an even-length palindrome
- `s = "a"` → `"a"`

## Constraints
- `1 ≤ |s| ≤ 5000` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary; the tests use lowercase letters.

## Target
Time: O(n²) with expand-around-center (O(n) with Manacher's algorithm, optional) · Space: O(1) (or O(n))

## Hints
<details><summary>Hint 1</summary>Every palindrome has a center: a character (odd length) or a gap between two characters (even length). If you grow outwards from each center while the two ends match, how many centers are there?</details>
<details><summary>Hint 2</summary>Checking every substring from scratch costs O(n³). Expanding from a center reuses the work of the smaller palindrome inside it. Manacher's algorithm goes further and reuses work between neighbouring centers, but O(n²) is the intended answer here.</details>
