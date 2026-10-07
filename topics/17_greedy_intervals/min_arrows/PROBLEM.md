# Minimum Arrows to Burst Balloons
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Minimum Number of Arrows to Burst Balloons" (title kept for cross-reference only)

## Problem
Each balloon is a horizontal span `{xstart, xend}` on a number line. An arrow shot straight up at
position `x` bursts every balloon whose span contains `x`. Return the **fewest arrows** that burst all
the balloons.

```cpp
int findMinArrowShots(std::vector<std::vector<int>> points);
```

**Interval convention: closed.** A span includes both of its ends, so balloons `{1, 2}` and `{2, 3}`
are both burst by one arrow at `2`. An empty input needs `0` arrows.

**Careful:** coordinates can be anywhere in the full `int` range, `-2147483648` to `2147483647`.
Computing `a - b` for two coordinates can overflow; compare with `<` instead of subtracting.

## Examples
- `{{10,16},{2,8},{1,6},{7,12}}` → `2` (an arrow at 6 bursts `{2,8}` and `{1,6}`; one at 11 bursts the others)
- `{{1,2},{3,4},{5,6},{7,8}}` → `4` (no two balloons share a point)
- `{{1,2},{2,3},{3,4},{4,5}}` → `2` (arrows at 2 and 4)

## Constraints
- 0 ≤ points.size() ≤ 10⁵; each span has xstart ≤ xend, both in [−2³¹, 2³¹ − 1].
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n log n) · Space: O(1) extra beyond sorting

## Hints
<details><summary>Hint 1</summary>Sort the balloons by their right end. Where is the best place to shoot the first arrow?</details>
<details><summary>Hint 2</summary>After placing an arrow at the right end of the first balloon, which following balloons does it already burst? When does the next arrow become necessary?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
