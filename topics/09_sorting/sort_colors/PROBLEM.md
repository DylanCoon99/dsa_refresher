# Sort Colors
**Topic:** 09 Sorting and Selection · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Sort Colors" (title kept for cross-reference only)

## Problem
`nums` holds only the values `0`, `1` and `2` (think red, white and blue). Rearrange it in
place so all the 0s come first, then all the 1s, then all the 2s. This is Dijkstra's "Dutch
national flag" problem.

Aim for a single pass over the array and O(1) extra space, without a library sort and
without counting the colors and rewriting. The tests only check the final arrangement, so
they cannot enforce the single pass or the space bound.

## Examples
- `{2, 0, 2, 1, 1, 0}` → `{0, 0, 1, 1, 2, 2}`
- `{2, 0, 1}` → `{0, 1, 2}`
- `{1}` → `{1}`

## Constraints
- 1 ≤ n ≤ 300
- nums[i] ∈ {0, 1, 2}

## Target
Time: O(n), one pass · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Keep three regions in the array: a prefix of 0s, a suffix of 2s, and a middle of 1s, with an unclassified stretch between them. Which index do you examine next?</details>
<details><summary>Hint 2</summary>When you find a 2 and swap it to the back, the element you swapped in has not been looked at yet. Should the scanning index advance? What about when you swap a 0 forward?</details>
