# Longest Increasing Subsequence
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Longest Increasing Subsequence" (title kept for cross-reference only)

## Problem
Return the length of the longest **strictly** increasing subsequence of `nums` (elements keep their
order but need not be adjacent; equal values do not count as increasing).

```cpp
int lengthOfLIS(const std::vector<int>& nums);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.
The state of the O(n²) solution is "the best subsequence **ending at** index i". The O(n log n) solution
keeps a different array: write down what its entries mean too.

## Examples
- `{10, 9, 2, 5, 3, 7, 101, 18}` → `4` (for example `2, 5, 7, 101`)
- `{0, 1, 0, 3, 2, 3}` → `4`
- `{7, 7, 7, 7}` → `1` (equal values are not strictly increasing)

## Constraints
- 1 ≤ nums.size() ≤ 10⁵; −10⁵ ≤ nums[i] ≤ 10⁵.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(n)

The large test uses n = 10⁵: the O(n²) DP needs about 5·10⁹ steps and times out, so the O(n log n) version is
required.

## CLRS (optional, ≈5 min)
- §15.4 (3e) / §14.4 (4e), "Longest common subsequence": the end-of-section exercises ask for an O(n²) and an O(n lg n) algorithm for the longest monotonically increasing subsequence (≈5 min). Attempt them before looking at hints.
- Skip if: you can describe both approaches and what each array stores.

## Hints
<details><summary>Hint 1</summary>Start with the O(n²) idea: <code>len[i]</code> is the longest increasing subsequence ending at index <code>i</code>. Which earlier indices can it extend?</details>
<details><summary>Hint 2</summary>Keep <code>tail[k]</code>, the smallest possible last value of an increasing subsequence of length <code>k+1</code>. Is <code>tail</code> sorted? What does binary search on it do for each new number (replace or append), and does "strictly" change which search you need?</details>
