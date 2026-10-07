# Daily Temperatures
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Daily Temperatures" (title kept for cross-reference only)

## Problem
`temperatures[i]` is the temperature on day `i`. For each day `i`, return how many days you
must wait until a **strictly warmer** day: the smallest `k > 0` with
`temperatures[i + k] > temperatures[i]`. If no later day is warmer, the answer for that day
is `0`. A day with an equal temperature does not count as warmer.

## Examples
- `{73, 74, 75, 71, 69, 72, 76, 73}` → `{1, 1, 4, 2, 1, 1, 0, 0}`
- `{30, 40, 50, 60}` → `{1, 1, 1, 0}`
- `{5, 5, 6}` → `{2, 1, 0}`; the equal 5 on day 1 does not count for day 0

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ temperatures[i] ≤ 10⁹ (wider than real temperatures, so a long strictly decreasing run is possible)

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Think of the days still waiting for a warmer day. How do their temperatures compare to each other, from the oldest waiting day to the newest?</details>
<details><summary>Hint 2</summary>When a new day arrives, which waiting days does it resolve, and are they together at one end of that list? Why is each day added and removed at most once?</details>
