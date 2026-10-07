# Valid Anagram
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Valid Anagram" (title kept for cross-reference only)

## Problem
Two strings are anagrams if one can be rearranged into the other, using every character
exactly once. Given `s` and `t`, return `true` if they are anagrams.

## Examples
- `s = "anagram", t = "nagaram"` → `true`
- `s = "rat", t = "car"` → `false`
- `s = "", t = ""` → `true` (both empty)

## Constraints
- Lowercase letters `a`–`z` only.
- Length of each string ≤ 5·10⁴ (a string may be empty).

## Target
Time: O(n) · Space: O(1) (26 counters)

## Hints
<details><summary>Hint 1</summary>If the lengths differ, you can answer immediately. Otherwise, what do two anagrams have in common letter by letter?</details>
<details><summary>Hint 2</summary>Would 26 counters, incremented for <code>s</code> and decremented for <code>t</code>, end up all zero exactly for anagrams?</details>
