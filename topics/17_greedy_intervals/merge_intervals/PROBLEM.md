# Merge Intervals
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Merge Intervals" (title kept for cross-reference only)

## Problem
Given a list of intervals `{start, end}` (with `start <= end`) in any order, merge every group of
overlapping intervals and return the merged list.

```cpp
std::vector<std::vector<int>> merge(std::vector<std::vector<int>> intervals);
```

**Interval convention: closed.** `{a, b}` contains every point from `a` to `b` including both ends, so
intervals that merely **touch** (`{1, 4}` and `{4, 5}`) overlap and are merged into `{1, 5}`.

The result contains pairwise non-overlapping intervals, **sorted by start**. An empty input gives an
empty result.

## Examples
- `{{1,3},{2,6},{8,10},{15,18}}` → `{{1,6},{8,10},{15,18}}` (`{1,3}` and `{2,6}` overlap)
- `{{1,4},{4,5}}` → `{{1,5}}` (touching counts as overlapping)
- `{{8,10},{1,3},{2,4}}` → `{{1,4},{8,10}}` (the input need not be sorted)

## Constraints
- 0 ≤ intervals.size() ≤ 10⁵; each interval has exactly two values with 0 ≤ start ≤ end ≤ 10⁹.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(n) for the output

The large test makes "merge any overlapping pair, repeat until nothing changes" (O(n²) or worse) time out.

## Hints
<details><summary>Hint 1</summary>If the intervals were sorted by start, which single earlier interval could the next one possibly overlap?</details>
<details><summary>Hint 2</summary>Keep the interval you are currently building. When the next start is at most its end, how does the end change? When it is larger, what must you do with the current one?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
