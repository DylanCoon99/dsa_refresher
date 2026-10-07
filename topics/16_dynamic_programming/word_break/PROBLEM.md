# Word Break
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Word Break" (title kept for cross-reference only)

## Problem
Given a string `s` and a list of words, decide whether `s` can be written as a concatenation of words from
the list. A word may be used any number of times (or not at all).

```cpp
bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `s = "leetcode"`, `wordDict = {"leet", "code"}` → `true`
- `s = "applepenapple"`, `wordDict = {"apple", "pen"}` → `true` (`"apple"` is used twice)
- `s = "catsandog"`, `wordDict = {"cats", "dog", "sand", "and", "cat"}` → `false`

## Constraints
- 1 ≤ s.size() ≤ 300; 1 ≤ wordDict.size() ≤ 1000; every word has 1 to 20 characters (no empty words).
- All characters are lowercase letters.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n · W · L) with W words of length at most L (or O(n · L) with a hash set of words) · Space: O(n)

The large test is a string where the cache-free recursion explores exponentially many splits before failing.

## Hints
<details><summary>Hint 1</summary>Let <code>ok[i]</code> mean "the first <code>i</code> characters can be split into words". What does the last word look like, and which earlier <code>ok</code> value does it need?</details>
<details><summary>Hint 2</summary>If you recurse from the front instead, which position is the state? How many distinct positions are there, compared with how many times a plain recursion reaches them?</details>
