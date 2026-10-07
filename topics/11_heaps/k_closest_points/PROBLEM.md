# K Closest Points to the Origin
**Topic:** 11 Heaps and Priority Queues · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "K Closest Points to Origin" (title kept for cross-reference only)

## Problem
Each point is a two-element vector `{x, y}`. Return the `k` points that are closest to the origin
`(0, 0)` by straight-line (Euclidean) distance. Compare squared distances `x² + y²`; no square
root is needed.

The answer is guaranteed to be unique: the k-th and (k+1)-th closest points never tie (when
`k = n` there is nothing to tie with). The returned points may be in **any order**; the tests
sort them before comparing. Points are 2-element vectors, and two different input points may be
equal.

In C++ a heap of the k best candidates so far is a `std::priority_queue` with a max-heap order on
distance (the default for a pair or tuple keyed on distance).

## Examples
- `points = {{1, 3}, {-2, 2}}, k = 1` → `{{-2, 2}}` (squared distances 10 and 8)
- `points = {{3, 3}, {5, -1}, {-2, 4}}, k = 2` → `{{3, 3}, {-2, 4}}` in any order (18, 26, 20)
- `points = {{0, 0}, {1, 1}}, k = 2` → both points

## Constraints
- 1 ≤ k ≤ n ≤ 10⁵
- −10⁴ ≤ x, y ≤ 10⁴ (so `x² + y²` ≤ 2·10⁸ fits in `int`)
- The answer is unique.

## Target
Time: O(n log k) · Space: O(k)

The large test (10⁵ points, k = 10) rejects quadratic work. An O(n log n) full sort also passes it
comfortably, so the test cannot tell that apart from the O(n log k) target; the target is stated
here instead. Quickselect gives O(n) on average and also passes.

## Hints
<details><summary>Hint 1</summary>You do not need the points sorted, only the k smallest by distance. How does a bounded collection of "best so far" help?</details>
<details><summary>Hint 2</summary>If you keep k candidates in a max-heap keyed by distance, which one is at the top, and when does a new point replace it?</details>
