# Car Fleet
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Car Fleet" (title kept for cross-reference only)

## Problem
Cars drive on a one-lane road toward a destination at mile `target`. Car `i` starts at
`position[i]` (all positions are different and below `target`) and drives at a constant
`speed[i]`. A car can never pass the car in front of it: if it catches up, it slows down and
travels bumper to bumper at the front car's speed. A *fleet* is a non-empty set of cars that
travel together at the same position and speed. A car that catches up with a fleet exactly at
`target` still counts as part of that fleet. A single car is a fleet, and a car that would only
catch up *after* passing the target is not part of the fleet ahead of it.

Return the number of fleets that arrive at `target`. The input cars are in no particular order.

## Examples
- `target = 12, position = {10, 8, 0, 5, 3}, speed = {2, 4, 1, 1, 3}` → `3`; the cars starting at 10 and 8 merge, so do 5 and 3, and 0 stays alone
- `target = 10, position = {0, 5}, speed = {2, 1}` → `1`; both reach the target at time 5
- `target = 10, position = {8, 0}, speed = {1, 4}` → `2`; the second car would only catch up at time 2.5, after the first car has finished at time 2

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ position[i] < target ≤ 10⁶, all positions distinct
- 1 ≤ speed[i] ≤ 10⁶

## Target
Time: O(n log n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>If no car ever slowed down, when would each car reach the target? Which car must you look at first, and what does a car behind it do if it arrives sooner than that?</details>
<details><summary>Hint 2</summary>Processing cars from the one closest to the target backwards, what single value do you need to remember about the current front fleet? Can you compare arrival times exactly, without floating-point error?</details>
