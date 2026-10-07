# Partition Equal Subset Sum
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Partition Equal Subset Sum" (title kept for cross-reference only)

## Problem
Decide whether the numbers in `nums` can be split into two groups (every number in exactly one group)
with equal sums.

```cpp
bool canPartition(const std::vector<int>& nums);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `{1, 5, 11, 5}` → `true` (`{1, 5, 5}` and `{11}`)
- `{1, 2, 3, 5}` → `false` (the total is 11, which is odd)
- `{4}` → `false` (one number cannot be split into two equal groups; the other group would be empty with sum 0)

## Constraints
- 1 ≤ nums.size() ≤ 200; 1 ≤ nums[i] ≤ 100; the sum is therefore at most 2·10⁴.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n · sum) · Space: O(sum)

The large test (n = 200) rejects enumerating all 2ⁿ subsets.

## Hints
<details><summary>Hint 1</summary>Two equal halves means one subset sums to exactly <code>total / 2</code>. When is that impossible right away?</details>
<details><summary>Hint 2</summary>Let <code>reach[s]</code> say whether some subset of the numbers seen so far sums to <code>s</code>. This is 0/1 knapsack with weight = value: in which direction must you loop over <code>s</code> so each number is used once?</details>
