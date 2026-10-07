# Palindrome Partitioning
**Topic:** 15 Backtracking · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Palindrome Partitioning" (title kept for cross-reference only)

## Problem
Given a string `s`, split it into consecutive non-empty pieces so that **every piece is a palindrome**, and
return all such splits. Each split is a list of the pieces in the order they appear in `s` (concatenating them
gives back `s`), so the order inside a split matters. The splits themselves may be returned in any order.

## Examples
- `s = "aab"` → `{{"a","a","b"}, {"aa","b"}}`
- `s = "a"` → `{{"a"}}`
- `s = "aaaa"` → 8 splits, e.g. `{"a","a","a","a"}`, `{"aa","aa"}`, `{"a","aaa"}`, `{"aaaa"}`

## Constraints
- 1 ≤ s.size() ≤ 12
- `s` is made of lowercase letters `'a'`–`'z'`

## Target
Time: O(n · 2ⁿ) · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>Choose the first piece: it is a prefix of the remaining string. Which prefixes are allowed?</details>
<details><summary>Hint 2</summary>After choosing a palindromic prefix, what remains is the same problem on a shorter suffix. When is a split complete?</details>
