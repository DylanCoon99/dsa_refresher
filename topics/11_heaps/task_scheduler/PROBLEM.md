# Task Scheduler
**Topic:** 11 Heaps and Priority Queues · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Task Scheduler" (title kept for cross-reference only)

## Problem
A CPU executes one task per time unit, or sits idle for a unit. Each task is a letter; tasks with
the same letter are of the same type. Between two executions of the **same** type there must be at
least `n` other time units (each either a different task or idle). Different types have no
restriction relative to each other. Tasks may be run in any order.

Return the minimum number of time units needed to finish all tasks.

## Examples
- `tasks = {'A','A','A','B','B','B'}, n = 2` → `8` (A B idle A B idle A B)
- `tasks = {'A','A','A','B','B','B'}, n = 0` → `6`
- `tasks = {'A','A','A','A','A','A','B','C','D','E','F','G'}, n = 1` → `12` (no idle time needed)

## Constraints
- 1 ≤ tasks.size() ≤ 10⁴
- Each task is an uppercase letter `'A'`–`'Z'`
- 0 ≤ n ≤ 100

## Target
Time: O(t) for t tasks (O(t log 26) with a heap) · Space: O(1), at most 26 task types

There is no large test: the input has at most 26 distinct letters, so every sensible approach is
fast and the tests only check correctness.

## Hints
<details><summary>Hint 1</summary>Only the counts of each letter matter. Which letter is the bottleneck, and what pattern of "frames" of length n + 1 does it force?</details>
<details><summary>Hint 2</summary>Greedy view: at every time unit, run the available type with the most tasks left. Alternatively, count the idle slots the most frequent type leaves and ask how many other tasks can fill them.</details>
