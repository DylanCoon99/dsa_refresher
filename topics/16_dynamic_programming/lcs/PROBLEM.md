# Longest Common Subsequence
**Topic:** 16 Dynamic Programming · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Common Subsequence" (title kept for cross-reference only)

## Problem
A *subsequence* of a string is what remains after deleting any number of characters (possibly none)
without reordering the rest. Find the length of the longest string that is a subsequence of both
`a` and `b`. Write it **twice**:

```cpp
int lcsMemo(const std::string& a, const std::string& b);  // top-down: recursion + cache
int lcsTab(const std::string& a, const std::string& b);   // bottom-up: fill a table
```

Return `0` if the strings share no character (or either is empty). The tests run the same cases
against both functions.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the
*evaluation order*. Then write the memoized version and convert it to the tabulated one.

## Examples
- `a = "abcde"`, `b = "ace"` → `3` (the common subsequence `"ace"`)
- `a = "abc"`, `b = "abc"` → `3`
- `a = "abc"`, `b = "def"` → `0`

## Constraints
- 0 ≤ a.size(), b.size() ≤ 1000 for `lcsTab`; 0 ≤ a.size(), b.size() ≤ 300 for `lcsMemo` (keeps recursion depth small).
- Both strings use lowercase letters `a`–`z`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(|a| · |b|) · Space: O(|a| · |b|) (the table version can be reduced to O(min(|a|, |b|)) with rolling rows)

The large test makes the cache-free recursion exponential, so it times out.

## CLRS (optional, ≈15 min)
- §15.4 (3e) / §14.4 (4e), "Longest common subsequence": the theorem on optimal substructure and the LCS-LENGTH procedure (≈15 min).
- Skip if: you can write the recurrence for `lcs(i, j)` including the case where the last characters differ.

## Hints
<details><summary>Hint 1</summary>Let <code>L[i][j]</code> be the LCS length of the first <code>i</code> characters of <code>a</code> and the first <code>j</code> of <code>b</code>. Look at the last characters <code>a[i-1]</code> and <code>b[j-1]</code>: what happens when they are equal?</details>
<details><summary>Hint 2</summary>When they differ, at least one of them is not in the answer. Which two smaller states cover both possibilities, and what does <code>L[0][j]</code> equal?</details>
