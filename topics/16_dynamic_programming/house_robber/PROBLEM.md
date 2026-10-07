# House Robber
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "House Robber" (title kept for cross-reference only)

## Problem
Houses stand in a row and `nums[i]` is the money in house `i`. You may take from any set of houses as long as
no two chosen houses are neighbours. Return the largest total you can take.

```cpp
int rob(const std::vector<int>& nums);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `{1, 2, 3, 1}` → `4` (houses 0 and 2)
- `{2, 7, 9, 3, 1}` → `12` (houses 0, 2 and 4)
- `{5}` → `5`

## Constraints
- 1 ≤ nums.size() ≤ 100; 0 ≤ nums[i] ≤ 1000.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Let <code>best[i]</code> be the most you can take from the first <code>i</code> houses. For house <code>i</code> there are two choices: skip it or take it. What does each one leave you with?</details>
<details><summary>Hint 2</summary>Which earlier values does <code>best[i]</code> read? Can you keep just those instead of the whole array?</details>
