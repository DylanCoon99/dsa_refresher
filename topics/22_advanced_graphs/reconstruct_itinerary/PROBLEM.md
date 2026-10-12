# Reconstruct Itinerary
**Topic:** 22 Advanced Graph Topics · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Reconstruct Itinerary" (title kept for cross-reference only)

## Problem
`tickets[i] = {from, to}` is a one-way flight between two airports named by strings. Build an itinerary that starts at `"JFK"` and uses **every ticket exactly once**. If several itineraries exist, return the **lexicographically smallest** one, comparing the sequences of airport names element by element. Two tickets with the same endpoints are two separate tickets. A valid itinerary is guaranteed to exist.

## Examples
- `{{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}}` → `JFK, NRT, JFK, KUL`: starting with `KUL` is smaller but strands the `NRT` tickets.
- `{{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}}` → `JFK, ATL, JFK, SFO, ATL, SFO`.
- `{{"JFK","LAX"}}` → `JFK, LAX`.

## Constraints
- 1 ≤ tickets ≤ 300 (limit chosen for this exercise; the tests use at most 8), airport names are non-empty strings, and a valid itinerary exists.
- The reference uses recursive DFS (depth up to the number of tickets); production code would use an explicit stack.

## Target
Time: O(E log E) · Space: O(E) · Where: E = number of tickets.

## CLRS (optional, ≈10 min)
- Ch. 22 (3e) / Ch. 20 (4e), end-of-chapter problem "Euler tour": read the statement and the idea of walking edges and splicing cycles.
- Skip if: you can explain why a directed graph whose edges are all connected has a closed tour using every edge once exactly when every vertex has equal in- and out-degree.

## Hints
<details><summary>Hint 1</summary>Always flying to the smallest destination can strand tickets. If you are stuck at an airport with no tickets left, where must that airport sit in the final route?</details>
<details><summary>Hint 2</summary>Run a DFS that always takes the smallest unused ticket and records an airport only when it has no tickets left. What order do the recorded airports come out in, and what fix does that suggest?</details>
