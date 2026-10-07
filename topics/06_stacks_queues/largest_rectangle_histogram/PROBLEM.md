# Largest Rectangle in Histogram
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Largest Rectangle in Histogram" (title kept for cross-reference only)

## Problem
`heights[i]` is the height of the `i`-th bar of a histogram; every bar has width 1 and the
bars sit side by side. Return the area of the largest rectangle that lies entirely inside the
histogram, i.e. a run of consecutive bars `l..r` with area `(r - l + 1) * min(heights[l..r])`.

## Examples
- `{2, 1, 5, 6, 2, 3}` → `10`; bars 5 and 6 give width 2 at height 5
- `{2, 4}` → `4`; either the single bar of height 4, or both bars at height 2
- `{3, 0, 3, 3}` → `6`; the zero splits the histogram, and the right side gives 2 x 3

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ heights[i] ≤ 10⁴ (so the answer fits in `int`)

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Fix the bar that is the shortest in the rectangle. How far can the rectangle extend to the left and to the right?</details>
<details><summary>Hint 2</summary>Those extents end at the nearest strictly shorter bar on each side. Can a stack of increasing heights find both while you scan once? What happens to the stack when a shorter bar arrives?</details>
