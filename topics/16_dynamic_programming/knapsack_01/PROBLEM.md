# 0/1 Knapsack
**Topic:** 16 Dynamic Programming · **Kind:** Implement · **Difficulty:** Medium

## Problem
There are `n` items; item `i` has a weight and a value. Choose a subset of the items (each at most
once) whose total weight is at most `capacity`, maximizing the total value. Write it **twice**:

```cpp
int knapsackMemo(const std::vector<int>& weights, const std::vector<int>& values, int capacity);  // top-down
int knapsackTab(const std::vector<int>& weights, const std::vector<int>& values, int capacity);   // bottom-up
```

Return the maximum total value (`0` if nothing fits or there are no items). `weights` and `values`
have the same length. The tests run the same cases against both functions.

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the
*evaluation order*. Then write the memoized version and convert it to the tabulated one.

## Examples
- `weights = {1, 3, 4, 5}`, `values = {1, 4, 5, 7}`, `capacity = 7` → `9` (items of weight 3 and 4)
- `weights = {5}`, `values = {10}`, `capacity = 4` → `0` (the only item is too heavy)
- `weights = {2, 2}`, `values = {3, 4}`, `capacity = 4` → `7` (both fit)

## Constraints
- 0 ≤ n ≤ 100; 1 ≤ weights[i] ≤ 10⁴; 0 ≤ values[i] ≤ 10⁴.
- 0 ≤ capacity ≤ 10⁴.
- These limits are chosen for this exercise; they cover every test input. The total value always fits in an `int`.

## Target
Time: O(n · capacity) · Space: O(n · capacity) for the memo; O(capacity) for the tabulated version.

The large test (100 items, capacity 10⁴) rejects the 2ⁿ subset enumeration.

## CLRS (optional, ≈10 min)
- §16.2 (3e) / §15.2 (4e), "Elements of the greedy strategy": read the 0-1 versus fractional knapsack contrast, which shows why greedy works for one and not the other (≈10 min).
- Skip if: you can give a tiny instance where taking the best value-per-weight item first is wrong for 0/1 knapsack.

## Hints
<details><summary>Hint 1</summary>For the tabulated version, one 1-D array <code>best[w]</code> (the best value with capacity <code>w</code>) is enough if you process the items one at a time and iterate the capacity <b>downward</b> from <code>capacity</code> to the item's weight. Why would iterating upward let an item be used twice?</details>
<details><summary>Hint 2</summary>For a single item, there are exactly two choices: leave it, or take it. Which smaller state does each choice lead to, and when is "take it" not allowed?</details>
