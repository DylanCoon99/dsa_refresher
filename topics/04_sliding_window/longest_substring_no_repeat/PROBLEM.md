# Longest Substring Without Repeating Characters
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Substring Without Repeating Characters" (title kept for cross-reference only)

## Problem
Given a string `s`, find the length of the longest *contiguous* substring in which no
character appears more than once. The empty string gives 0.

## Examples
- `s = "abcabcbb"` → `3` (`"abc"`)
- `s = "bbbbb"` → `1` (`"b"`)
- `s = "pwwkew"` → `3` (`"wke"`; `"pwke"` is not contiguous)

## Constraints
- 0 ≤ n ≤ 5·10⁴
- `s` consists of printable ASCII characters (codes 32 to 126)

## Target
Time: O(n) · Space: O(alphabet)

## Hints
<details><summary>Hint 1</summary>When the character at the right end was already seen inside the window, where must the window's left end move to?</details>
<details><summary>Hint 2</summary>If you store each character's last position, can the left end jump straight there? Is it ever correct to move the left end backward?</details>
