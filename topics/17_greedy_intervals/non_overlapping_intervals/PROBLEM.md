# Non-overlapping Intervals
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Non-overlapping Intervals" (title kept for cross-reference only)

## Problem
Given a list of intervals `{start, end}`, return the **minimum number of intervals to remove** so that
the remaining ones are pairwise non-overlapping.

```cpp
int eraseOverlapIntervals(std::vector<std::vector<int>> intervals);
```

**Interval convention: half-open.** `{start, end}` covers `[start, end)`, so intervals that merely
**touch** (`{1, 2}` and `{2, 3}`) do **not** overlap and can both stay. Two intervals overlap exactly
when each one starts before the other ends.

## Examples
- `{{1,2},{2,3},{3,4},{1,3}}` → `1` (remove `{1,3}`)
- `{{1,2},{1,2},{1,2}}` → `2` (keep one copy)
- `{{1,2},{2,3}}` → `0` (touching is not overlapping)

## Constraints
- 0 ≤ intervals.size() ≤ 10⁵; every interval has 0 ≤ start < end ≤ 10⁹ (non-empty; this exercise's own restriction).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(1) extra beyond sorting

The large test makes an O(n²) dynamic program over the sorted intervals time out.

## CLRS (optional, ≈15 min)
- §16.1 (3e) / §15.1 (4e), "An activity-selection problem": this is the same problem (keep the largest
  set of compatible intervals; the answer is n minus that). Read the greedy-choice theorem statement (≈15 min).
- Skip if: you can state why sorting by end time is safe.

## Hints
<details><summary>Hint 1</summary>Removing the fewest intervals is the same as keeping the most. Which interval should you commit to first if you want to leave the most room for the others?</details>
<details><summary>Hint 2</summary>Sort by end time. Keep an interval whenever it starts at or after the end of the last one you kept; what do you do otherwise?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
