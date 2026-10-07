# Insert Interval
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Insert Interval" (title kept for cross-reference only)

## Problem
You are given a list of intervals `{start, end}` that is **already sorted by start and pairwise
non-overlapping**, plus one new interval. Insert the new interval, merging it with every interval it
overlaps, and return the resulting sorted, non-overlapping list.

```cpp
std::vector<std::vector<int>> insert(std::vector<std::vector<int>> intervals, std::vector<int> newInterval);
```

**Interval convention: closed.** `{a, b}` contains both `a` and `b`, so intervals that merely **touch**
(`{1, 4}` and `{4, 5}`) overlap and merge into `{1, 5}`. In the input list, no two intervals overlap or
touch.

## Examples
- `{{1,3},{6,9}}` insert `{2,5}` → `{{1,5},{6,9}}`
- `{{1,2},{3,5},{6,7},{8,10},{12,16}}` insert `{4,8}` → `{{1,2},{3,10},{12,16}}` (swallows three intervals)
- `{}` insert `{5,7}` → `{{5,7}}`

## Constraints
- 0 ≤ intervals.size() ≤ 10⁵; 0 ≤ start ≤ end ≤ 10⁹ for every interval including the new one; the input list is sorted by start and no two of its intervals overlap or touch.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(n) for the output

## Hints
<details><summary>Hint 1</summary>The list is sorted, so the intervals fall into three groups relative to the new one: entirely before it, overlapping it, entirely after it. How do you recognize each group?</details>
<details><summary>Hint 2</summary>For the overlapping group, what are the start and end of the single interval that replaces them all?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
