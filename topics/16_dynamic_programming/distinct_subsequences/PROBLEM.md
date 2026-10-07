# Distinct Subsequences
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Distinct Subsequences" (title kept for cross-reference only)

## Problem
Count how many different ways `t` can be obtained as a subsequence of `s`. A way is a set of positions in `s`
(in increasing order) whose characters spell `t`; two ways are different if they use different positions,
even when they spell the same word.

```cpp
int numDistinct(const std::string& s, const std::string& t);
```

An empty `t` can be formed in exactly one way (choose no positions). If `t` is longer than `s` the answer is `0`.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `s = "rabbbit"`, `t = "rabbit"` → `3` (three choices of which `b` to drop)
- `s = "babgbag"`, `t = "bag"` → `5`
- `s = "abc"`, `t = ""` → `1`

## Constraints
- 0 ≤ s.size(), t.size() ≤ 1000; lowercase letters only.
- The final answer is guaranteed to fit in a 32-bit `int`. Intermediate counts need not: for `s = "a"×500 + "b"` and `t = "a"×250 + "c"` the table passes through values around C(500, 250), far beyond even `long long`, and the answer is 0.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(|s| · |t|) · Space: O(|t|) with a rolling row (O(|s| · |t|) for the full table)

## Hints
<details><summary>Hint 1</summary>Let <code>ways[i][j]</code> be the number of ways the first <code>j</code> characters of <code>t</code> appear in the first <code>i</code> characters of <code>s</code>. What is <code>ways[i][0]</code>? What is <code>ways[0][j]</code> for <code>j &gt; 0</code>?</details>
<details><summary>Hint 2</summary>Look at <code>s[i-1]</code>. You can always skip it. When can you also use it as the last matched character, and which cell does that come from? Keep the counts in <code>unsigned long long</code>: its wraparound is defined, and the result is exact whenever the true answer fits in 32 bits. A signed table overflows on the "a"/"c" input above and the sanitizer build reports a crash.</details>
