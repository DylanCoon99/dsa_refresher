# Target Sum
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Target Sum" (title kept for cross-reference only)

## Problem
Put a `+` or a `-` in front of every number in `nums`, so the numbers add up to an expression. Count the
sign assignments whose value equals `target`. Two assignments are different if some position gets a different
sign, even if the numbers there are equal (or zero).

```cpp
int findTargetSumWays(const std::vector<int>& nums, int target);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `{1, 1, 1, 1, 1}`, `target = 3` → `5` (choose which one of the five ones gets `-`)
- `{1}`, `target = 1` → `1`
- `{0, 0, 1}`, `target = 1` → `4` (each 0 can take either sign)

## Constraints
- 1 ≤ nums.size() ≤ 20; 0 ≤ nums[i] ≤ 1000; the sum of nums is at most 1000; −1000 ≤ target ≤ 1000.
- There are at most 2²⁰ sign assignments, so the answer fits in an `int`.
- These limits are chosen for this exercise; they cover every test input. With n ≤ 20 even plain 2ⁿ enumeration is fast enough, so the tests do not require the DP; do it as practice.

## Target
Time: O(n · sum) · Space: O(sum) · Where: n = nums.size(), sum = total of all values in nums.

## Hints
<details><summary>Hint 1</summary>Let <code>P</code> be the sum of the numbers with <code>+</code> and <code>N</code> the sum with <code>-</code>. You know <code>P - N = target</code> and <code>P + N = total</code>. What single subset-sum question does that turn into?</details>
<details><summary>Hint 2</summary>When is that subset sum impossible regardless of the numbers (parity, sign, size)? And how does a <code>0</code> change the count of subsets with a given sum?</details>
