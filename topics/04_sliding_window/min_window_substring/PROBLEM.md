# Minimum Window Substring
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Minimum Window Substring" (title kept for cross-reference only)

## Problem
Given strings `s` and `t`, return the shortest contiguous substring of `s` that contains every
character of `t`, counting multiplicity: if `t` has two `a`s, the window needs at least two `a`s.
If no such window exists, return the empty string `""`. When several shortest windows tie,
any one is accepted.

## Examples
- `s = "ADOBECODEBANC", t = "ABC"` → `"BANC"`
- `s = "a", t = "a"` → `"a"`
- `s = "a", t = "aa"` → `""` (`s` has only one `a`)

## Constraints
- 1 ≤ |s|, |t| ≤ 10⁵
- both strings consist of ASCII letters (upper and lower case)

## Target
Time: O(|s| + |t|) · Space: O(alphabet)

## Hints
<details><summary>Hint 1</summary>Keep how many characters of `t` are still missing from the window. Expand the right end until that number is 0.</details>
<details><summary>Hint 2</summary>Once the window covers `t`, how long can you keep shrinking from the left while it still covers `t`? Where should you record the best window?</details>
