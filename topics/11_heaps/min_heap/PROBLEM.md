# Min Heap
**Topic:** 11 Heaps and Priority Queues · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement a binary min-heap of `int` stored in an array (a `std::vector<int>`):

```cpp
class MinHeap {
public:
    MinHeap();                                // empty heap
    explicit MinHeap(std::vector<int> values); // heapify the given values
    void push(int v);                         // insert v
    int pop();                                // remove and return the smallest value
    int top() const;                          // the smallest value, heap unchanged
    std::size_t size() const;
    bool empty() const;
};
```

Rules:
- Build it yourself on a plain array. Do **not** use `std::priority_queue`, `std::make_heap`,
  `std::push_heap` or `std::pop_heap`.
- The `std::vector<int>` constructor must heapify in O(n) using bottom-up sift-down, not by
  pushing the values one at a time.
- `pop()` and `top()` on an empty heap throw `std::out_of_range`.
- Duplicates are allowed and each copy is a separate element.

If you are used to Python's `heapq`: in C++ you would normally reach for `std::priority_queue<int>`
(a max-heap) or `std::priority_queue<int, std::vector<int>, std::greater<>>` (a min-heap), and
negation is unnecessary. Here you write the min-heap yourself.

## Examples
- Push 5, 2, 8, 1: `top()` is `1`, `size()` is `4`; `pop()` returns `1, 2, 5, 8` in that order.
- `MinHeap h({9, 4, 7, 1})`: `pop()` returns `1`, then `4`, then `7`, then `9`.
- `MinHeap h; h.pop();` throws `std::out_of_range`.

## Constraints
- Any `int` values, including `INT_MIN` and `INT_MAX`; duplicates allowed.
- The largest test pushes 4·10⁵ values and then pops all of them.

## Target
Time: O(log n) per `push` and `pop`, O(1) `top`, O(n) for the vector constructor · Space: O(n)

What the tests can and cannot tell apart: the large test rejects an O(n) insert per push (for
example a sorted vector, which is O(n²) overall). It does **not** check that the vector
constructor is linear. Pushing n values one by one and then using the constructor look the same
to the tests, so the O(n) heapify is something you must verify by reasoning.

## CLRS (optional, ≈20 min)
- §6.1–6.3 (3e) / §6.1–6.3 (4e), "Heaps", "Maintaining the heap property" and "Building a heap": the index arithmetic, MAX-HEAPIFY, and the O(n) bound for BUILD-MAX-HEAP. CLRS uses a max-heap; flip the comparisons.
- Skip if: you can explain why bottom-up heapify is linear.

## Hints
<details><summary>Hint 1</summary>With the root at index 0, where do the children and the parent of index i live? Which two operations restore the heap property: one after adding at the end, one after moving the last element to the root?</details>
<details><summary>Hint 2</summary>For the constructor, which indices already satisfy the heap property trivially (they have no children)? If you sift down starting from the last index that has a child and walk back to the root, why is the total work O(n) rather than O(n log n)?</details>
