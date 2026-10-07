# Longest Palindromic Subsequence
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Palindromic Subsequence" (title kept for cross-reference only)

## Problem
Return the length of the longest subsequence of `s` that reads the same forwards and backwards. A subsequence
keeps the original order of its characters but they need not be adjacent.

```cpp
int longestPalindromeSubseq(const std::string& s);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `"bbbab"` → `4` (`"bbbb"`)
- `"cbbd"` → `2` (`"bb"`)
- `"a"` → `1`

## Constraints
- 1 ≤ s.size() ≤ 1000; lowercase letters only.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n²) · Space: O(n²) (O(n) with rolling rows)

The large test (n = 1000) rejects the 2ⁿ enumeration and the cache-free recursion.

## CLRS (optional, ≈5 min)
- Ch. 15 (3e) / Ch. 14 (4e), "Dynamic Programming": the end-of-chapter problem "Longest palindrome subsequence" (≈5 min). Try it before the hints; it can be solved by a state over substrings, or by reducing it to a problem you have already solved.
- Skip if: you can state the recurrence on a substring `s[i..j]` and its base cases.

## Hints
<details><summary>Hint 1</summary>Let <code>L[i][j]</code> be the answer for the substring <code>s[i..j]</code>. Compare <code>s[i]</code> with <code>s[j]</code>. What happens when they are equal?</details>
<details><summary>Hint 2</summary>When they differ, at least one end is unused. Which two smaller substrings cover that? In what order must you fill the table so those cells are ready (by substring length)? Alternatively: how does the longest palindromic subsequence relate to the LCS of <code>s</code> and its reverse?</details>
