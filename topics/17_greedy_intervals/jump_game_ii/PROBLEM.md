# Jump Game II
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Jump Game II" (title kept for cross-reference only)

## Problem
You stand on index `0` of an array of non-negative integers. From index `i` you may jump to any index
from `i` to `i + nums[i]`. Return the **minimum number of jumps** needed to reach the last index.
The last index is always reachable in the inputs given to you.

```cpp
int jump(const std::vector<int>& nums);
```

## Examples
- `{2,3,1,1,4}` → `2` (0 → 1 → 4)
- `{2,3,0,1,4}` → `2` (0 → 1 → 4; the `0` is never used)
- `{5}` → `0` (already on the last index)

## Constraints
- 1 ≤ nums.size() ≤ 10⁵; 0 ≤ nums[i] ≤ 10⁴; the last index is reachable.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

The large test makes an O(n · max(nums)) dynamic program time out.

## Hints
<details><summary>Hint 1</summary>Think of the indices reachable with exactly k jumps as a window. What is the window for k + 1 jumps?</details>
<details><summary>Hint 2</summary>While scanning inside the current window, what single value do you track so you know where the next window ends? When do you commit to another jump?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
