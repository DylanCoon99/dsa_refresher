# Jump Game
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Jump Game" (title kept for cross-reference only)

## Problem
You stand on index `0` of an array of non-negative integers. From index `i` you may jump to any index
from `i` to `i + nums[i]` (a jump of length 0 stays in place). Return whether you can reach the **last**
index.

```cpp
bool canJump(const std::vector<int>& nums);
```

## Examples
- `{2,3,1,1,4}` → `true` (0 → 1 → 4)
- `{3,2,1,0,4}` → `false` (every route ends on the `0` at index 3, which cannot move)
- `{0}` → `true` (you are already on the last index)

## Constraints
- 1 ≤ nums.size() ≤ 10⁵; 0 ≤ nums[i] ≤ 10⁴.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

The large test makes a search that tries every possible jump from every index (up to n · 10⁴ work) time out.

## Hints
<details><summary>Hint 1</summary>Instead of tracking which exact indices are reachable, track one number while scanning left to right. What is it?</details>
<details><summary>Hint 2</summary>If the scan reaches an index beyond the farthest position you could have reached so far, what does that tell you?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
