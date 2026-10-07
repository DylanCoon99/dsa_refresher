# Counting Bits
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Counting Bits" (title kept for cross-reference only)

## Problem
Given `n ≥ 0`, return a vector `ans` of length `n + 1` where `ans[i]` is the number of 1 bits in
the binary representation of `i`, for every `0 ≤ i ≤ n`.

## Examples
- `n = 2` → `{0, 1, 1}`
- `n = 5` → `{0, 1, 1, 2, 1, 2}`
- `n = 0` → `{0}`

## Constraints
- 0 ≤ n ≤ 10⁷

## Target
Time: O(n) using a recurrence on earlier answers · Space: O(n) for the output
(Counting each number's bits separately also passes the tests; the O(n) recurrence is the learning target.)

## Hints
<details><summary>Hint 1</summary>How does the bit count of `i` relate to the bit count of `i >> 1`? What bit was dropped?</details>
<details><summary>Hint 2</summary>If you already have the answers for all smaller numbers, can you write `ans[i]` in terms of one of them plus the lowest bit of `i`?</details>
