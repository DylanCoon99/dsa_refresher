# Meeting Rooms II
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Meeting Rooms II" (a premium problem on LeetCode; it is restated here in original words, and Car Pooling is the free alternative in this topic; title kept for cross-reference only)

## Problem
Each meeting is an interval `{start, end}`. Return the **minimum number of rooms** needed so that every
meeting gets a room and no room hosts two meetings at the same time.

```cpp
int minMeetingRooms(const std::vector<std::vector<int>>& intervals);
```

**Interval convention: half-open.** A meeting occupies `[start, end)`. A meeting that ends at time `t`
and one that starts at time `t` do **not** overlap, so they can share a room. An empty input needs
`0` rooms.

## Examples
- `{{0,30},{5,10},{15,20}}` → `2` (`{0,30}` runs alongside each of the others, which never overlap each other)
- `{{7,10},{2,4}}` → `1`
- `{{1,5},{2,6},{3,7}}` → `3` (all three are running at time 3)

## Constraints
- 0 ≤ intervals.size() ≤ 10⁵; every meeting has 0 ≤ start < end ≤ 10⁹ (non-empty; this exercise's own restriction).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>The number of rooms needed equals the largest number of meetings running at the same moment. How can you find that number?</details>
<details><summary>Hint 2</summary>Sort the starts and the ends separately and walk through them, or keep a min-heap of the end times of the meetings in progress. What should happen when the next meeting starts exactly when the earliest one ends?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
