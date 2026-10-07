# Reverse Bits
**Topic:** 18 Bit Manipulation and Mathematics · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Reverse Bits" (title kept for cross-reference only)

## Problem
Reverse the order of the 32 bits of an unsigned 32-bit integer: bit 0 becomes bit 31, bit 1 becomes
bit 30, and so on. Leading zeros count, so the result is always read as a full 32-bit pattern.

## Examples
- `n = 1` → `0x80000000` (the lowest bit moves to the highest position)
- `n = 0x0000000F` → `0xF0000000`
- `n = 0xFFFFFFFF` → `0xFFFFFFFF`

## Constraints
- `n` is any `std::uint32_t`

## Target
Time: O(32) = O(1) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Take the lowest bit of `n`, append it to the end of a result you are building, then shift `n` down. How many times must you repeat this?</details>
<details><summary>Hint 2</summary>If you must always do exactly 32 steps (not stop when `n` becomes 0), what does that do for inputs with leading zeros?</details>
