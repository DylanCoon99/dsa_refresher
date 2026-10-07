# Backtracking Templates
**Topic:** 15 Backtracking · **Kind:** Implement · **Difficulty:** Medium

## Problem
Write the three classic enumeration routines. Each one is the same
choose → explore → unchoose recursion with a different "what can I choose next?" rule.

```cpp
std::vector<std::vector<int>> allSubsets(const std::vector<int>& items);
std::vector<std::vector<int>> allPermutations(const std::vector<int>& items);
std::vector<std::vector<int>> allCombinations(int n, int k);
```

- `items` are distinct integers.
- `allSubsets` returns every subset of `items` (2ⁿ of them, including `{}` and the full set). Inside each
  subset the elements keep the relative order they have in `items`. The order of the subsets in the
  result is up to you.
- `allPermutations` returns every ordering of `items` (n! of them). The order of the permutations is
  up to you; the order inside each permutation matters.
- `allCombinations(n, k)` returns every way to choose `k` values from `1..n`, each combination in
  ascending order (C(n, k) of them). The order of the combinations is up to you. `k = 0` gives `{{}}`.
- With empty `items`, both `allSubsets` and `allPermutations` return `{{}}` (one empty result, not zero).
- No result may appear twice.

## Examples
- `allSubsets({1, 2, 3})` → `{{}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3}}` (any order)
- `allPermutations({1, 2, 3})` → the 6 orderings of 1, 2, 3 (any order)
- `allCombinations(4, 2)` → `{{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}}` (any order)

## Constraints
- 0 ≤ items.size() ≤ 8, items distinct, −100 ≤ items[i] ≤ 100
- 0 ≤ k ≤ n ≤ 8

## Target
Time: O(n · 2ⁿ) for subsets, O(n · n!) for permutations, O(k · C(n, k)) for combinations (output-sensitive) · Space: O(n) recursion depth beyond the output

## Hints
<details><summary>Hint 1</summary>

The shared skeleton, in pseudocode:

```
explore(state):
    if state is complete:        # or: at every node, for subsets
        record a copy of state
        return
    for each choice allowed from here:
        choose(choice)           # push onto the path / mark as used
        explore(state)
        unchoose(choice)         # pop / unmark, restoring state exactly
```

Which part differs between subsets, permutations and combinations: when you record, and which choices are allowed?
</details>
<details><summary>Hint 2</summary>For subsets and combinations, what single number can you pass down so you never pick an earlier element again? For permutations, what do you need to remember instead?</details>
