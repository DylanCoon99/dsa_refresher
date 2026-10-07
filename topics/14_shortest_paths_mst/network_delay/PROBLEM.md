# Network Delay
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Network Delay Time" (title kept for cross-reference only)

## Problem
A network has `n` nodes labeled `1 .. n`. Each entry of `times` is `{u, v, w}`: a signal sent from
`u` reaches `v` after `w` time units (the link is directed). A signal starts at node `k` at time 0
and is forwarded along every outgoing link of every node it reaches.

Return the time at which the last node receives the signal, i.e. the largest shortest-path
distance from `k`. If some node can never receive it, return `-1`. If `n = 1`, the answer is `0`.

## Examples
- `times = {{2,1,1},{2,3,1},{3,4,1}}, n = 4, k = 2` → `2` (node 4 is reached last, via 2 → 3 → 4)
- `times = {{1,2,1}}, n = 2, k = 1` → `1`
- `times = {{1,2,1}}, n = 2, k = 2` → `-1` (the link only goes from 1 to 2, so node 1 is never reached)

## Constraints
- 1 ≤ n ≤ 100; 1 ≤ k ≤ n.
- 0 ≤ times.size() ≤ 6000; each entry has three integers, with 1 ≤ u, v ≤ n and u ≠ v.
- 0 ≤ w ≤ 100. The same ordered pair `{u, v}` may appear more than once.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O((V + E) log V) · Space: O(V + E)

## Hints
<details><summary>Hint 1</summary>When does node v hear the signal? Think of the earliest arrival time at each node as a shortest-path distance from k.</details>
<details><summary>Hint 2</summary>Once you have all the distances, what do you need to report, and what does an unreached node tell you?</details>
