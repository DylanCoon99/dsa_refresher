# Maximum Overlap
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Implement · **Difficulty:** Medium

## Problem
Given a list of intervals, return the largest number of intervals that are active at the same instant.
Use the **sweep-line** technique: turn each interval into two events (a start and an end), sort the
events by time, and walk through them keeping a running count of active intervals.

```cpp
int maxOverlap(const std::vector<std::pair<int,int>>& intervals);
```

**Interval convention: half-open.** `{start, end}` is active on `[start, end)`: it includes `start` but
not `end`. Two intervals that merely touch (`{1, 3}` and `{3, 5}`) do **not** overlap. In your event
order, an **end must be processed before a start at the same time**.

An empty input returns `0`.

## Examples
- `{{1,4},{2,5},{3,6}}` → `3` (all three are active at time 3)
- `{{1,3},{3,5}}` → `1` (touching intervals never overlap)
- `{{1,10},{2,3},{4,5}}` → `2` (the small ones never overlap each other)

## Constraints
- 0 ≤ intervals.size() ≤ 10⁵; every interval has 0 ≤ start < end ≤ 10⁹ (non-empty; this exercise's own restriction).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(n)

The large test makes counting the active intervals at every start point (O(n²)) time out.

## CLRS (optional, ≈5 min)
- §16.1 (3e) / §15.1 (4e), "An activity-selection problem": the end-of-section exercise on scheduling
  activities among the fewest lecture halls (interval-graph coloring) is exactly this problem (≈5 min).
- Skip if: you can explain why the number of lecture halls needed equals the maximum overlap.

## Hints
<details><summary>Hint 1</summary>Only the moments when an interval starts or ends can change the count. How can you list those moments in order?</details>
<details><summary>Hint 2</summary>If one interval ends at time 3 and another starts at time 3, should the count briefly be 2 or not? Which event must come first?</details>
<details><summary>Hint 3</summary>An alternative to events is a min-heap of end times; either works, but this exercise asks for the sweep line.</details>
<details><summary>Hint 4</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
