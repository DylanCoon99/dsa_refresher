# Number of 1 Bits
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Number of 1 Bits" (title kept for cross-reference only)

## Problem
Given a 32-bit unsigned integer `n`, return how many of its bits are set to 1 (its Hamming weight).

## Examples
- `n = 11` (binary `1011`) → `3`
- `n = 128` (binary `10000000`) → `1`
- `n = 0xFFFFFFFF` → `32`

## Constraints
- `n` is any `std::uint32_t`, 0 ≤ n ≤ 2³² − 1

## Target
Time: O(number of set bits) (or O(32)) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>What does `n & (n - 1)` do to the lowest set bit of `n`? Try it on `1011` and on `1000`.</details>
<details><summary>Hint 2</summary>If one step removes exactly one set bit, how many steps does it take to reach 0?</details>
