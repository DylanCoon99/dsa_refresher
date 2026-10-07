# Coin Change II
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Coin Change II" (title kept for cross-reference only)

## Problem
Count the combinations of coins (each denomination usable any number of times) that add up to exactly
`amount`. Combinations are unordered: using 1 then 2 is the same combination as 2 then 1.

```cpp
int change(int amount, const std::vector<int>& coins);
```

An amount of `0` has exactly one combination (use no coins). Return `0` if no combination exists.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `amount = 5`, `coins = {1, 2, 5}` → `4` (5; 2+2+1; 2+1+1+1; 1×5)
- `amount = 3`, `coins = {2}` → `0`
- `amount = 3`, `coins = {1, 2}` → `2` (1+1+1, 1+2)

## Constraints
- 1 ≤ coins.size() ≤ 300, coins are distinct integers in [1, 5000], in any order; 0 ≤ amount ≤ 5000.
- The final answer is guaranteed to fit in a 32-bit `int`. Intermediate table entries need not: with even coins only, a table entry for an even sum can be huge while the answer for an odd amount is 0 or small.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(amount · coins.size()) · Space: O(amount)

## Hints
<details><summary>Hint 1</summary>If you loop over amounts in the outer loop and coins in the inner loop you count ordered sequences. Which loop must be outer so each combination is counted once?</details>
<details><summary>Hint 2</summary>Process one denomination at a time and let <code>ways[a]</code> be the number of combinations of the denominations processed so far. Why does going upward over <code>a</code> allow unlimited reuse of the current coin? Keep the table in <code>unsigned long long</code>: its wraparound is defined, and the result is exact whenever the true answer fits. A signed 32-bit table overflows on the way and is reported as a crash by the sanitizer build.</details>
