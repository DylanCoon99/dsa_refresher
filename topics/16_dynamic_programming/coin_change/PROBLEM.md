# Coin Change
**Topic:** 16 Dynamic Programming · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Coin Change" (title kept for cross-reference only)

## Problem
Given coin denominations and a target amount, find the fewest coins that add up to exactly the amount.
Every denomination can be used any number of times. Write it **twice**:

```cpp
int coinChangeMemo(const std::vector<int>& coins, int amount);  // top-down: recursion + cache
int coinChangeTab(const std::vector<int>& coins, int amount);   // bottom-up: fill a table
```

Both return the minimum number of coins, or `-1` if no combination reaches `amount`. An amount of `0`
needs `0` coins. The tests run the same cases against both functions.

**Before coding, write a comment** with the four parts of every DP: the *state* (what does one
table cell / one recursive call mean?), the *transition* (how is it computed from smaller states?),
the *base cases*, and the *evaluation order* (which states must be ready first?). Then write the
memoized version and convert it to the tabulated one.

## Examples
- `coins = {1, 2, 5}`, `amount = 11` → `3` (5 + 5 + 1)
- `coins = {2}`, `amount = 3` → `-1` (no way to make an odd amount from 2s)
- `coins = {1, 3, 4}`, `amount = 6` → `2` (3 + 3; taking the biggest coin first would give 4 + 1 + 1)

## Constraints
- 1 ≤ coins.size() ≤ 12; coins are distinct integers in [1, 10⁴], in any order.
- 0 ≤ amount ≤ 10⁴ for `coinChangeTab`, 0 ≤ amount ≤ 10³ for `coinChangeMemo` (keeps recursion depth small).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(amount · coins.size()) · Space: O(amount)

The large test makes plain recursion with no cache exponential, so it times out.

## CLRS (optional, ≈20 min)
- §15.1 (3e) / §14.1 (4e), "Rod cutting": read the naive recursion, then the top-down memoized and bottom-up versions side by side (≈20 min).
- Skip if: you can convert a memoized recursion into a bottom-up loop (and back) without help.

## Hints
<details><summary>Hint 1</summary>Let <code>best[a]</code> be the fewest coins that make exactly <code>a</code>. Which smaller amounts can <code>a</code> be reached from?</details>
<details><summary>Hint 2</summary>If the last coin used is <code>c</code>, what must the rest of the solution be? What should an unreachable amount hold so it never wins a minimum?</details>
