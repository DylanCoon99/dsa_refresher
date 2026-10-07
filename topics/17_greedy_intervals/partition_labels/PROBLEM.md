# Partition Labels
**Topic:** 17 Greedy Algorithms and Intervals · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Partition Labels" (title kept for cross-reference only)

## Problem
Cut a string of lowercase letters into as many contiguous pieces as possible so that **no letter appears
in more than one piece**. Return the lengths of the pieces, in order.

```cpp
std::vector<int> partitionLabels(const std::string& s);
```

## Examples
- `"ababcbacadefegdehijhklij"` → `{9, 7, 8}` (`"ababcbaca"`, `"defegde"`, `"hijhklij"`)
- `"eccbbbbdec"` → `{10}` (the letters `e`, `c` and `b` tie everything together)
- `"abc"` → `{1, 1, 1}`

## Constraints
- 1 ≤ s.size() ≤ 10⁵; s uses only the letters `'a'` to `'z'`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1) (26 letters)

## Hints
<details><summary>Hint 1</summary>For each letter, where is its last occurrence? A piece containing a letter must reach at least that far.</details>
<details><summary>Hint 2</summary>As you scan, keep the farthest "last occurrence" of every letter seen in the current piece. When does the scan position equal that farthest end?</details>
<details><summary>Hint 3</summary>Before coding, write one sentence on why the greedy choice is safe (the exchange argument).</details>
