# Alien Dictionary
**Topic:** 22 Advanced Graph Topics · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Alien Dictionary" (a premium problem; title kept for cross-reference only; the statement below is written in original words)

## Problem
A dictionary of words is sorted according to an unknown alphabet, with the usual rule that words are compared at the first position where they differ, and that a word comes before any longer word that it is a prefix of. The words use only lowercase English letters.

Return a string containing **every distinct letter that appears in `words` exactly once**, ordered so that `words` is sorted under it. If several orders work, any is accepted. If no order works (the words contradict each other, or a longer word is listed before its own prefix), return `""`.

## Examples
- `{"wrt","wrf","er","ett","rftt"}` → a valid order such as `"wertf"`: the adjacent pairs give t < f, w < e, r < t, e < r.
- `{"z","x"}` → `"zx"`.
- `{"abc","ab"}` → `""`: the longer word comes first although the shorter is its prefix.

## Constraints
- 1 ≤ words.size() ≤ 100 and every word is non-empty lowercase text (limits chosen for this exercise; the tests use at most 12 words of at most 4 letters, plus a handful of short fixed cases).
- Adjacent words may be equal.

## Target
Time: O(total characters + A²) for alphabet size A · Space: O(A²)

## Hints
<details><summary>Hint 1</summary>Which pairs of words actually tell you something about letter order, and which position inside such a pair carries the information?</details>
<details><summary>Hint 2</summary>Once you have "a before b" facts between letters, what standard graph routine turns them into an order, and how does it report a contradiction? Don't forget letters that never appear in a fact.</details>
