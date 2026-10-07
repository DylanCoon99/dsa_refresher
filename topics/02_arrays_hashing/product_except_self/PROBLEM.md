# Product of Array Except Self
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Product of Array Except Self" (title kept for cross-reference only)

## Problem
Given a list `nums`, return a list `answer` of the same length where `answer[i]` is the
product of every element of `nums` except `nums[i]`. **Do not use division.** Every prefix
product and every suffix product fits in a 32-bit `int`.

## Examples
- `nums = {1, 2, 3, 4}` → `{24, 12, 8, 6}`
- `nums = {-1, 1, 0, -3, 3}` → `{0, 0, 9, 0, 0}`
- `nums = {5, 2}` → `{2, 5}`

## Constraints
- 2 ≤ n ≤ 10⁵
- −30 ≤ nums[i] ≤ 30

## Target
Time: O(n) · Space: O(1) extra, not counting the output list

## Hints
<details><summary>Hint 1</summary>Split the product for position i into two parts: everything to the left of i, and everything to the right of i.</details>
<details><summary>Hint 2</summary>Can you fill the answer with left products in one pass, then sweep right-to-left multiplying in a running right product?</details>
