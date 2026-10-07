# Two Sum
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Two Sum" (title kept for cross-reference only)

## Problem
You are given a list of integers `nums` and an integer `target`. Find two *different
positions* `i` and `j` with `i < j` such that `nums[i] + nums[j] == target`, and return
them as `{i, j}`. At least one such pair exists. If more than one does, any is accepted.
A single element may not be paired with itself.

## Examples
- `nums = {2, 7, 11, 15}, target = 9` → `{0, 1}` (2 + 7 = 9)
- `nums = {3, 2, 4}, target = 6` → `{1, 2}`; positions 0 and 0 would reuse the 3
- `nums = {3, 3}, target = 6` → `{0, 1}`

## Constraints
- 2 ≤ n ≤ 2·10⁵
- −10⁹ ≤ nums[i], target ≤ 10⁹

## Target
Time: O(n) · Space: O(n)

## CLRS (optional, ≈10 min)
- §11.2 (3e) / §11.2 (4e), "Hash tables": read the intro and the theorem statements on expected search time with chaining. Skip the proofs.
- Skip if: you can explain why a hash-map lookup is O(1) on average but O(n) in the worst case.

## Hints
<details><summary>Hint 1</summary>For a fixed j, which value would nums[i] have to be?</details>
<details><summary>Hint 2</summary>Can you remember the values you've already passed so that question becomes an O(1) lookup?</details>
