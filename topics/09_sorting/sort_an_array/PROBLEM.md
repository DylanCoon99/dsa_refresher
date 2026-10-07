# Sort an Array
**Topic:** 09 Sorting and Selection · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Sort an Array" (title kept for cross-reference only)

## Problem
Sort a vector of integers into non-decreasing order, **in place**, three times over: once
with each of the three classic algorithms. One header holds all three functions:

- `void mergeSort(std::vector<int>& a)`: a merge sort.
- `void quickSort(std::vector<int>& a)`: a quicksort (Lomuto or Hoare partitioning, your choice).
- `void heapSort(std::vector<int>& a)`: a heapsort.

Do not call `std::sort`, `std::stable_sort` or `std::partial_sort` to do the work. The tests
only look at the final order, so they cannot enforce this; it is on the honor system, and the
exercise is pointless if you skip the algorithms. The tests also cannot tell which algorithm
a function uses, so each function should really implement the algorithm its name says.

The large tests will punish a quicksort that picks a fixed pivot (first, last or middle element)
with plain Lomuto partitioning: sorted input and all-equal input drive it to quadratic time.
Pick the pivot randomly (or by median of three) and decide how equal keys are handled.

## Examples
- `{5, 2, 3, 1}` → `{1, 2, 3, 5}`
- `{5, 1, 1, 2, 0, 0}` → `{0, 0, 1, 1, 2, 5}`
- `{}` → `{}`

## Constraints
- 0 ≤ n ≤ 2·10⁵
- Any `int` value, including `INT_MIN` and `INT_MAX` (do not compute `a - b` to compare).

## Target
Time: O(n log n) (merge sort and heapsort worst case; quicksort expected) · Space: O(n) merge sort, O(1) extra heapsort, O(log n) extra quicksort

## CLRS (optional, ≈10–20 min per algorithm; read only the one you are implementing)
- Merge sort: §2.3 (3e) / §2.3 (4e), "Designing algorithms": MERGE and MERGE-SORT pseudocode (≈15 min).
- Quicksort: §7.1 (3e) / §7.1 (4e), "Description of quicksort": PARTITION, the Lomuto scheme (≈15 min); then §7.3 (3e) / §7.3 (4e), "A randomized version of quicksort" (≈5 min). Hoare's scheme is the subject of an end-of-chapter problem in Ch. 7.
- Heapsort: §6.4 (3e) / §6.4 (4e), "The heapsort algorithm" (≈10 min).
- Skip each if you can write that algorithm from memory.

## Hints
<details><summary>Hint 1</summary>Merge sort: if two halves are already sorted, how much work does it take to combine them? Do you need a scratch buffer, and can you allocate it once?</details>
<details><summary>Hint 2</summary>Quicksort: after one partition, where does the pivot end up for good? What happens to the sizes of the two sides when the input is already sorted, or when every element equals the pivot, and what could you do about equal keys (e.g. a three-way split)?</details>
<details><summary>Hint 3</summary>Heapsort: build a max-heap in the array itself, then repeatedly swap the root to the end of the shrinking heap and sift down. Which index is the last non-leaf node?</details>
