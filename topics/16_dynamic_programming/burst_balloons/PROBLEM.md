# Burst Balloons
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Burst Balloons" (title kept for cross-reference only)

## Problem
Balloon `i` has the number `nums[i]` on it. You burst all balloons one at a time. Bursting balloon `i` earns
`left * nums[i] * right` coins, where `left` and `right` are the numbers on the nearest balloons that have not
burst yet on each side. If there is no such balloon on a side, use the number `1` there. Return the maximum
total coins over all bursting orders.

```cpp
int maxCoins(const std::vector<int>& nums);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.
Hint for your design: think about which balloon is burst **last** in a range, not first.

## Examples
- `{3, 1, 5, 8}` → `167` (burst 1, 5, 3, 8: 3·1·5 + 3·5·8 + 1·3·8 + 1·8·1 = 15 + 120 + 24 + 8)
- `{1, 5}` → `10` (burst 1 first: 1·1·5 = 5, then 5: 1·5·1 = 5)
- `{7}` → `7`

## Constraints
- 1 ≤ nums.size() ≤ 300; 0 ≤ nums[i] ≤ 100. The answer is at most 300 · 100³ = 3·10⁸, so it fits in an `int`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n³) · Space: O(n²)

The large test (n = 300) rejects the n! enumeration of bursting orders.

## Hints
<details><summary>Hint 1</summary>If you choose the <em>first</em> balloon to burst in a range, the remaining balloons' neighbours change and the two sides are no longer independent. What if you choose the <em>last</em> one to burst in the range instead?</details>
<details><summary>Hint 2</summary>Pad the array with a <code>1</code> at each end. Let <code>best[i][j]</code> be the maximum coins from bursting everything strictly between <code>i</code> and <code>j</code>. If <code>k</code> is the last one burst there, what are its neighbours at that moment, and which two smaller ranges remain? Fill the table by increasing range length.</details>
