# Segment Tree
**Topic:** 20 Range Query Structures · **Kind:** Implement · **Difficulty:** Hard

## Problem
Build a `SegmentTree` over an array of `long long` values that supports range sums and point assignment:

- `SegmentTree(values)`: build the tree from `values` (non-empty).
- `update(i, value)`: **assign** `value` to position `i` (replace, not add).
- `query(l, r)`: the sum of positions `l..r` inclusive, with `l <= r`.

The array length need not be a power of two; handle e.g. `n = 7` correctly.

Optional extension (not tested): add *lazy propagation* so that a whole range can be incremented or assigned in O(log n). Try it after the tests pass.

## Examples
- `values = {2, 4, 6, 8}` → `query(0, 3) = 20`, `query(1, 2) = 10`
- then `update(1, 10)` → `query(0, 3) = 26`, `query(1, 1) = 10`
- `values = {5}` → `query(0, 0) = 5`

## Constraints
- 1 ≤ n ≤ 10⁵ (limit chosen for this exercise); indices are always in range.
- |values[i]|, |value| ≤ 10⁹; sums fit in `long long`. At most 10⁵ calls per test.

## Target
Time: O(n) build, O(log n) per call · Space: O(n)

## CLRS (optional, ≈10 min)
- Ch. 14 (3e) / Ch. 17 (4e), "Augmenting Data Structures": read the §14.2 (3e) / §17.2 (4e) intro, "How to augment a data structure". It gives the general idea of storing extra information in each node. Segment trees themselves are not in CLRS.
- Skip if: you can explain what summary each node stores here and how an update re-derives it from its two children.

## Mastery
With brief reference.

## Hints
<details><summary>Hint 1</summary>Each node covers a range of positions and stores that range's sum. How does a node's value follow from its two children?</details>
<details><summary>Hint 2</summary>A query range overlaps a node's range in one of three ways: not at all, fully, or partially. What do you return in each case, and why does that visit only O(log n) nodes?</details>
