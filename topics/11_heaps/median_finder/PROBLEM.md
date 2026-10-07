# Median Finder
**Topic:** 11 Heaps and Priority Queues · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Find Median from Data Stream" (title kept for cross-reference only)

## Problem
Implement a class that maintains a growing collection of integers and reports its median:

```cpp
class MedianFinder {
public:
    void addNum(int num);          // add one value
    double findMedian() const;     // the median of all values added so far
};
```

The median of an odd count is the middle value of the sorted collection; for an even count it is
the average of the two middle values. `findMedian` is never called while the collection is empty.

Compute the average in `double`: the sum of two `int` values can overflow `int` (for example
`INT_MAX + INT_MAX`), so convert before adding. Duplicates count separately.

## Examples
- Add 1, 2: median `1.5`. Add 3: median `2.0`.
- Add 5: median `5.0`. Add -1: median `2.0`.
- Add `INT_MAX`, `INT_MAX`: median `2147483647.0`.

## Constraints
- Up to 10⁵ values, each −2³¹ ≤ value ≤ 2³¹ − 1 (full `int` range).
- Calls to `addNum` and `findMedian` may be interleaved in any order.

## Target
Time: O(log n) per `addNum`, O(1) per `findMedian` · Space: O(n)

The large test (10⁵ adds, each followed by a query) rejects sorting the collection on every query.
It is not designed to reject every O(n)-per-add method, such as inserting into a sorted vector;
the target is stated here instead.

## CLRS (optional, ≈10 min)
- §6.5 (3e) / §6.5 (4e), "Priority queues": the operations a priority queue supports and how a heap implements them.
- Skip if: you can say which heap operations you need here and what each costs.

## Hints
<details><summary>Hint 1</summary>The median sits at the boundary between the smaller half and the larger half. Which half would you like quick access to the largest element of, and which to the smallest?</details>
<details><summary>Hint 2</summary>Keep the smaller half in a max-heap and the larger half in a min-heap. What size relationship between the two heaps must hold after every insert, and how do you restore it when it breaks?</details>
