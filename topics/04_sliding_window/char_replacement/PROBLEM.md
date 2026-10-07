# Longest Repeating Character Replacement
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Repeating Character Replacement" (title kept for cross-reference only)

## Problem
You are given a string `s` of uppercase letters and an integer `k`. You may change at most
`k` characters of `s` to any uppercase letter. Return the length of the longest substring
that can be made to consist of one repeated letter using at most `k` changes.

## Examples
- `s = "ABAB", k = 2` → `4` (change both `B`s, or both `A`s)
- `s = "AABABBA", k = 1` → `4` (`"AABA"` becomes `"AAAA"`)
- `s = "ABC", k = 0` → `1` (no changes allowed, so the longest run is a single letter)

## Constraints
- 1 ≤ n ≤ 10⁵
- `s` consists of uppercase letters `A`–`Z`
- 0 ≤ k ≤ n

## Target
Time: O(n) · Space: O(1) (26 counters)

## Hints
<details><summary>Hint 1</summary>For a fixed window, how many changes are needed to make it uniform? Which letter should you keep?</details>
<details><summary>Hint 2</summary>The window is valid when (length − count of its most frequent letter) ≤ k. Do you really need the exact maximum after the left end moves, or is an over-estimate that never decreases still safe because you only care about finding a longer window?</details>
