# Container With Most Water
**Topic:** 03 Two Pointers · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Container With Most Water" (title kept for cross-reference only)

## Problem
`height[i]` is the height of a vertical wall standing at x = `i`. Pick two different walls
`i < j`. Together with the x-axis they form an open-topped container whose width is `j - i`
and whose water level is limited by the shorter wall, so it holds `(j - i) * min(height[i], height[j])`.
Return the largest amount of water any pair of walls can hold. Walls between the two chosen
ones are ignored (they do not block anything).

## Examples
- `height = {1, 8, 6, 2, 5, 4, 8, 3, 7}` → `49` (walls at x = 1 and x = 8: width 7, height 7)
- `height = {1, 1}` → `1`
- `height = {4, 3, 2, 1, 4}` → `16` (the two 4s are 4 apart)

## Constraints
- 2 ≤ n ≤ 10⁵
- 0 ≤ height[i] ≤ 10⁴

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Start with the widest container (first and last wall). Each step inward loses width, so what must improve for the area to grow?</details>
<details><summary>Hint 2</summary>Moving the taller wall inward can never help, because the shorter wall still limits the height while the width shrinks. Which wall should move?</details>
