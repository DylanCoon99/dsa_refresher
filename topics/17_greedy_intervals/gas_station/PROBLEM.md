# Gas Station
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Gas Station" (title kept for cross-reference only)

## Problem
`n` gas stations sit on a circular road. Station `i` offers `gas[i]` units of fuel, and driving from
station `i` to station `i + 1` (wrapping from the last back to station 0) costs `cost[i]` units. Your
tank is empty and unlimited in size; you start at some station, fill up there, and drive clockwise.
Return the index of the station you can start from to complete the full circle, or `-1` if there is none.

```cpp
int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost);
```

You must have enough fuel for each leg before you set off on it (arriving with exactly `0` left is fine).
In the inputs given to you there is **at most one** valid starting station.

## Examples
- `gas = {1,2,3,4,5}`, `cost = {3,4,5,1,2}` → `3` (from station 3 the tank after each leg is 3, 6, 4, 2, 0; never negative)
- `gas = {2,3,4}`, `cost = {3,4,3}` → `-1` (total gas 9 is less than total cost 10)
- `gas = {5}`, `cost = {4}` → `0`

## Constraints
- 1 ≤ n ≤ 10⁵; 0 ≤ gas[i], cost[i] ≤ 10⁴; at most one valid starting station exists.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

The large test makes simulating the trip from every station (O(n²)) time out.

## Hints
<details><summary>Hint 1</summary>If the total gas is less than the total cost, can any start work? And if it is at least the total cost, can you be sure a start exists?</details>
<details><summary>Hint 2</summary>Suppose you start at A and first run dry on the leg to station B. Could any station strictly between A and B have worked as a start? Where should you try next?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
