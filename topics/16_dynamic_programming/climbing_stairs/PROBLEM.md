# Climbing Stairs
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Climbing Stairs" (title kept for cross-reference only)

## Problem
A staircase has `n` steps. Each move climbs either 1 or 2 steps. Count the distinct sequences of moves that
climb exactly `n` steps.

```cpp
int climbStairs(int n);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `n = 2` → `2` (1+1, 2)
- `n = 3` → `3` (1+1+1, 1+2, 2+1)
- `n = 4` → `5`

## Constraints
- 1 ≤ n ≤ 45 (the answer for 45 is 1836311903, which fits in a 32-bit `int`).

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Think about the very last move. From which two earlier steps could you have come?</details>
<details><summary>Hint 2</summary>Does the answer for step <code>i</code> need the whole table, or only the previous two values?</details>
