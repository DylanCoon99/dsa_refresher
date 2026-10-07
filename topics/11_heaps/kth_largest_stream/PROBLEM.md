# Kth Largest in a Stream
**Topic:** 11 Heaps and Priority Queues · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Kth Largest Element in a Stream" (title kept for cross-reference only)

## Problem
Implement a class that tracks the k-th largest value of a growing collection of integers.
"k-th largest" means the k-th position in descending sorted order, so duplicates count separately:
in `{5, 5, 3}` the 2nd largest is `5` and the 3rd largest is `3`.

```cpp
class KthLargest {
public:
    KthLargest(int k, const std::vector<int>& nums); // start with the values in nums
    int add(int val);                                // insert val, return the current k-th largest
};
```

Guarantee: after every `add` the collection holds at least `k` values (so `nums` has at least
`k - 1` elements).

In C++ a min-heap is `std::priority_queue<int, std::vector<int>, std::greater<>>`; a plain
`std::priority_queue<int>` is a max-heap.

## Examples
- `k = 3, nums = {4, 5, 8, 2}`: `add(3)` → `4`, `add(5)` → `5`, `add(10)` → `5`, `add(9)` → `8`, `add(4)` → `8`
- `k = 1, nums = {}`: `add(-3)` → `-3`, then `add(-1)` → `-1`
- `k = 3, nums = {1, 2}`: `add(3)` → `1` (the collection is `{1, 2, 3}`)

## Constraints
- 1 ≤ k ≤ 10⁴
- k − 1 ≤ nums.size() ≤ 10⁵ (the tests use at most 10⁴ initial values)
- −10⁹ ≤ values ≤ 10⁹ (so the tests may use the full `int` range)
- Up to 10⁵ calls to `add`.

## Target
Time: O(log k) per `add` (the constructor is O(m log k) for m initial values) · Space: O(k)

The large test (k = 10⁴, 10⁵ adds) rejects re-sorting or re-scanning the whole collection on
every `add`. It is not designed to tell an O(log k) heap from slower-but-not-quadratic variants.

## Hints
<details><summary>Hint 1</summary>You only ever need the k largest values seen so far. What do you do with the others?</details>
<details><summary>Hint 2</summary>If you keep exactly the k largest in a min-heap, which element of the heap is the answer, and which element is the next one to be evicted?</details>
