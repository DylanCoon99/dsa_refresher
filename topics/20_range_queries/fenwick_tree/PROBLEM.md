# Fenwick Tree
**Topic:** 20 Range Query Structures · **Kind:** Implement · **Difficulty:** Medium

## Problem
Build a `FenwickTree` (binary indexed tree) over `n` positions numbered `0` to `n - 1`, all starting at `0`:

- `FenwickTree(n)`: create the structure with `n` zeros.
- `add(i, delta)`: add `delta` (may be negative) to position `i`.
- `prefixSum(i)`: the sum of positions `0..i` inclusive. `prefixSum(-1)` is `0` (the empty prefix).
- `rangeSum(l, r)`: the sum of positions `l..r` inclusive, with `l <= r`.

The API is 0-indexed. A Fenwick tree is naturally 1-indexed (the lowest set bit of an index decides how many positions a cell covers), so convert inside your class. All sums use `long long`.

## Examples
- `n = 5`; `add(0, 3)`, `add(2, 4)`, `add(4, -1)` → `prefixSum(2) = 7`, `prefixSum(4) = 6`, `rangeSum(1, 3) = 4`
- `n = 1`; `add(0, 9)` → `prefixSum(0) = 9`, `prefixSum(-1) = 0`
- `n = 3`; nothing added → `rangeSum(0, 2) = 0`

## Constraints
- 1 ≤ n ≤ 10⁶; indices are always in range (`0 <= i < n`, `-1 <= i` for `prefixSum`, `0 <= l <= r < n`).
- |delta| ≤ 10⁹; every running sum fits in `long long`. At most 10⁶ calls per test (limits chosen for this exercise; the tests stay inside them).

## Target
Time: O(log n) per call · Space: O(n)

## Mastery
From memory.

## Hints
<details><summary>Hint 1</summary>Cell `j` (1-indexed) stores the sum of the `j & -j` positions ending at `j`. How does a prefix query decompose into such blocks?</details>
<details><summary>Hint 2</summary>Querying walks `j -= j & -j`; updating walks `j += j & -j`. Why do those two walks visit exactly the blocks that contain, respectively, the prefix and the changed position?</details>
