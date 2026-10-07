# House Robber II
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "House Robber II" (title kept for cross-reference only)

## Problem
Same as House Robber, but the houses stand in a **circle**: the last house is a neighbour of the first.
No two neighbouring houses may both be chosen. Return the largest total you can take.

```cpp
int rob(const std::vector<int>& nums);
```

With one house there is nobody to conflict with. With two houses they are neighbours, so you take one.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `{2, 3, 2}` → `3` (houses 0 and 2 are neighbours in the circle, so take house 1)
- `{1, 2, 3, 1}` → `4` (houses 0 and 2)
- `{4, 4, 4}` → `4` (any two of three houses are neighbours)

## Constraints
- 1 ≤ nums.size() ≤ 100; 0 ≤ nums[i] ≤ 1000.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Houses 0 and n-1 can never both be chosen. How many separate straight-line problems cover every allowed choice?</details>
<details><summary>Hint 2</summary>Can you reuse the line-street solution on two sub-ranges? Watch the case n = 1, where one of the ranges would be empty.</details>
