# Car Pooling
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Car Pooling" (title kept for cross-reference only; the free alternative to the premium Meeting Rooms II)

## Problem
A car drives in one direction along a road and has `capacity` seats. Each trip is
`{passengers, from, to}`: that many passengers get in at position `from` and get out at position `to`.
Return whether the car can complete every trip without ever carrying more than `capacity` passengers.

```cpp
bool carPooling(const std::vector<std::vector<int>>& trips, int capacity);
```

**Interval convention: half-open.** A trip occupies seats on `[from, to)`. At a position where some
passengers leave and others board, the **leaving passengers get out first**, so a trip ending at `p` and a
trip starting at `p` never count together. Trips are given in no particular order.

## Examples
- `trips = {{2,1,5},{3,3,7}}`, `capacity = 4` → `false` (5 passengers between positions 3 and 5)
- `trips = {{2,1,5},{3,3,7}}`, `capacity = 5` → `true`
- `trips = {{3,2,7},{3,7,9}}`, `capacity = 3` → `true` (the first group leaves at 7 as the second boards)

## Constraints
- 1 ≤ capacity ≤ 10⁹; 0 ≤ trips.size() ≤ 10⁵; each trip has 1 ≤ passengers ≤ 100 and 0 ≤ from < to ≤ 10⁹.
- These limits are chosen for this exercise; they cover every test input. Positions go up to 10⁹, so an array with one cell per position is far too big.

## Target
Time: O(n log n) · Space: O(n)

The large test spreads trips over positions up to 10⁹, so only a sweep over the trip endpoints is feasible.

## Hints
<details><summary>Hint 1</summary>The passenger count changes only at the `from` and `to` positions. How can you list those changes in order?</details>
<details><summary>Hint 2</summary>At the same position, should a drop-off be applied before or after a pick-up? What happens to the running total if you get that wrong?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
