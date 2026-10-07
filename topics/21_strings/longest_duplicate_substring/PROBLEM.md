# Longest Duplicate Substring
**Topic:** 21 String Algorithms · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Longest Duplicate Substring" (title kept for cross-reference only)

## Problem
Return a longest substring of `s` that occurs at least twice. The two occurrences are allowed to overlap. If several substrings tie for the longest length, return any one of them; if no substring occurs twice (for example, all characters are distinct), return the empty string.

## Examples
- `s = "banana"` → `"ana"`: it occurs at positions 1 and 3 and the occurrences overlap
- `s = "abcd"` → `""`: no repeats
- `s = "aaaa"` → `"aaa"`: positions 0 and 1

## Constraints
- `1 ≤ |s| ≤ 3 · 10⁴` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary; the tests use lowercase letters.

## Target
Time: O(n log n) expected, using binary search on the length plus a rolling hash (a suffix array also works) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>If some substring of length L occurs twice, then so does some substring of length L - 1 (just drop the last character of both). What does that monotonicity let you do with L?</details>
<details><summary>Hint 2</summary>For a fixed L, how do you find a repeated length-L window in O(n)? Hash every window with a rolling hash and look for equal hashes. Hashes can collide, so verify a hash hit by comparing the two substrings directly before accepting it.</details>
