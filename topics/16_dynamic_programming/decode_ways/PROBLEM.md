# Decode Ways
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Decode Ways" (title kept for cross-reference only)

## Problem
Letters are encoded as numbers: `A` → 1, `B` → 2, …, `Z` → 26. A digit string `s` can be decoded by cutting it
into pieces, each of which is one of those numbers written **without a leading zero** (so `"06"` is not
`"6"`, and `"0"` is not a code). Count the ways to cut `s` into valid pieces.

```cpp
int numDecodings(const std::string& s);
```

Return `0` if no valid cutting exists.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `"12"` → `2` (`"1","2"` = AB, or `"12"` = L)
- `"226"` → `3` (BZ, VF, BBF)
- `"06"` → `0` (a piece cannot start with 0)

## Constraints
- 1 ≤ s.size() ≤ 100 and s contains only the digits `0`–`9`.
- The final answer is guaranteed to fit in a 32-bit `int` (so a string such as 100 ones is not a valid input). Intermediate counts can be larger than the final answer: for 45 ones followed by `"00"` they reach 1836311903 before the last `0` turns the answer into 0. That still fits in `int`, so `int` suffices for the tests.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1) with two rolling values (O(n) for a table or memo)

The large test includes a string that makes every branch of the cache-free recursion fail only at the very end,
so that version takes exponentially long.

## Hints
<details><summary>Hint 1</summary>Let <code>ways[i]</code> be the number of ways to decode the first <code>i</code> characters. The last piece is either one digit or two digits. When is each one valid?</details>
<details><summary>Hint 2</summary>A <code>'0'</code> can only be the second digit of <code>"10"</code> or <code>"20"</code>. What should each of the two transitions contribute when the digits don't form a valid piece?</details>
<details><summary>Hint 3</summary>Intermediate counts can be larger than the final answer. <code>int</code> intermediates suffice for the tests here, but using 64-bit values (for example <code>unsigned long long</code>, whose wraparound is defined) is a safe habit when the answer is small yet the intermediates are not.</details>
