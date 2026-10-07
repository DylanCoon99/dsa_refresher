# Permutation in String
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Permutation in String" (title kept for cross-reference only)

## Problem
Given two strings `s1` and `s2`, return `true` if some contiguous substring of `s2` is a
rearrangement (permutation) of `s1`, i.e. has exactly the same letters with the same counts.
Otherwise return `false`.

## Examples
- `s1 = "ab", s2 = "eidbaooo"` → `true` (`"ba"` is a permutation of `"ab"`)
- `s1 = "ab", s2 = "eidboaoo"` → `false` (`b` and `a` are never adjacent)
- `s1 = "abc", s2 = "abc"` → `true`

## Constraints
- 1 ≤ |s1|, |s2| ≤ 10⁵
- both strings consist of lowercase letters `a`–`z`

## Target
Time: O(|s1| + |s2|) · Space: O(1) (26 counters)

## Hints
<details><summary>Hint 1</summary>A permutation of `s1` has a fixed length. What does that say about the size of the window you need to examine?</details>
<details><summary>Hint 2</summary>When such a window slides one step, only two letters change. Can you update a count comparison in O(1) instead of recomparing all 26 counts?</details>
