# Find the First Occurrence of a String
**Topic:** 21 String Algorithms · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Find the Index of the First Occurrence in a String" (title kept for cross-reference only)

## Problem
Return the smallest index `i` such that `haystack` contains `needle` starting at position `i`, or `-1` if `needle` does not occur. An empty `needle` returns `0`. Solve it with KMP (the plan's requirement); a library `find` would pass the tests but skip the point of the exercise.

## Examples
- `haystack = "sadbutsad"`, `needle = "sad"` → `0`: the first occurrence wins even though there is a second one
- `haystack = "leetcode"`, `needle = "leeto"` → `-1`
- `haystack = "abc"`, `needle = "c"` → `2`: a match at the very end

## Constraints
- `0 ≤ |haystack|, |needle| ≤ 10⁶` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary; the tests use lowercase letters.

## Target
Time: O(n + m) · Space: O(m) · Where: n = haystack length, m = needle length.

## CLRS (optional, ≈5 min)
- §32.1 (3e) / §32.1 (4e), "The naive string-matching algorithm": read it to see the O(nm) baseline that the large test is built to defeat. The linear-time algorithm is in the `kmp` exercise (§32.4).
- Skip if: you can explain why the naive method does about n·m comparisons on `aaaa…a` against `aaa…ab`.

## Hints
<details><summary>Hint 1</summary>You may have already written the machinery in the `kmp` exercise. How would you stop at the first match instead of collecting all of them?</details>
<details><summary>Hint 2</summary>A common trick is to run the prefix function on `needle + '#' + haystack` (a separator not in either string). Where in that combined array does a value equal to `|needle|` first appear, and how does that convert to an index in `haystack`?</details>
