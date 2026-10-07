# Window Template
**Topic:** 04 Sliding Window · **Kind:** Implement · **Difficulty:** Medium

## Problem
Write a reusable variable-size sliding window:

```cpp
template <typename Valid>
int longestValidWindow(const std::string& s, Valid is_valid);
```

`is_valid(freq, window_len)` is called with the character counts of a window and its length,
and returns whether the window is acceptable:

- `freq` is a `const std::unordered_map<char,int>&`. It may contain keys whose count is 0
  (so a predicate should look only at positive counts).
- `window_len` is the number of characters in the window.
- The predicate is **monotone**: if a window is valid, every sub-window of it is valid too.
  The empty window is always valid.

Return the length of the longest contiguous substring of `s` for which `is_valid` is true
(0 for the empty string). Your template must work for any monotone predicate, so it must not
assume anything about what the predicate checks.

## Examples
- `s = "eceba"`, predicate "at most 2 distinct characters" → `3` (`"ece"`)
- `s = "abcabcbb"`, predicate "no repeated character" → `3` (`"abc"`)
- `s = "aaabb"`, predicate "`window_len - maxfreq <= 1`" → `4` (`"aaab"`: one change makes it uniform)

## Constraints
- 0 ≤ |s| ≤ 10⁵
- `is_valid` costs at most O(alphabet) per call; the alphabet is small (≤ 128 symbols)

## Target
Time: O(n · cost of is_valid) · Space: O(alphabet)

## Hints
<details><summary>Hint 1</summary>Keep a left and a right end. What should happen to the frequency map each time the right end advances?</details>
<details><summary>Hint 2</summary>Because the predicate is monotone, once a window is invalid, can it become valid again by growing it? What does that tell you about when to move the left end?</details>
