# Cheapest Flights Within K Stops
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Cheapest Flights Within K Stops" (title kept for cross-reference only)

## Problem
There are `n` cities `0 .. n-1`. Each entry of `flights` is `{from, to, price}`: a one-way flight.
Return the cheapest total price of a trip from `src` to `dst` that makes **at most `k` stops**
(intermediate cities, not counting `src` and `dst`), so it uses at most `k + 1` flights. If no
such trip exists, return `-1`.

Careful: the cheapest route overall may use too many stops. A plain Dijkstra on price alone can
settle a city through a cheap route that is already out of stops, and then miss a pricier route
that would still have stops left.

## Examples
- `n = 4, flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}}, src = 0, dst = 3, k = 1` → `700` (0 → 1 → 3; the cheaper 0 → 1 → 2 → 3 costs 400 but has 2 stops)
- `n = 3, flights = {{0,1,100},{1,2,100},{0,2,500}}, src = 0, dst = 2, k = 1` → `200`
- `n = 3, flights = {{0,1,100},{1,2,100},{0,2,500}}, src = 0, dst = 2, k = 0` → `500` (only the direct flight is allowed)

## Constraints
- 1 ≤ n ≤ 100; 0 ≤ src, dst < n and `src ≠ dst`; 0 ≤ k < n.
- 0 ≤ flights.size() ≤ n(n−1)/2; each entry has three integers with `from ≠ to` and
  1 ≤ price ≤ 10⁴. There is at most one flight for each ordered pair `{from, to}`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(k · E) · Space: O(V)

## CLRS (optional, ≈15 min)
- §24.1 (3e) / §22.1 (4e), "The Bellman-Ford algorithm": the relaxation rounds. After round i the distances are exact over paths with at most i edges, which is why `k + 1` rounds bound the number of flights (≈15 min).
- Skip if: you can explain why exactly `k + 1` rounds are enough, and why each round must read the previous round's distances, not the ones just updated.

## Hints
<details><summary>Hint 1</summary>A route with at most k stops has at most k + 1 flights. If you relax every flight once per round, what does the distance array describe after round i?</details>
<details><summary>Hint 2</summary>Why can a flight relaxed in round i be allowed to extend a path found in the same round? Which array should a round read from, and which should it write to?</details>
