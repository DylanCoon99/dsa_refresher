# 09 · Sorting and Selection
Run everything: `./dsa test 09` · Status: `./dsa list 09`

## Diagnostic
Attempt cold (≤ 40 min each): `sort_colors`, `kth_largest_array`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Insertion sort, merge sort, quicksort (including partition schemes and pivot selection), and heapsort.
- [ ] Counting sort and radix sort.
- [ ] Stability.
- [ ] The Ω(n log n) lower bound for comparison sorting.
- [ ] The default sorts used by standard libraries (Timsort, introsort).
- [ ] Quickselect.
- [ ] Custom comparators.

## Implement
- [ ] `sort_an_array`: merge sort, quicksort (Lomuto or Hoare partitioning) and heapsort in one header (also a Practice problem below) · `./dsa test 09/sort_an_array`
- [ ] `quickselect`: the k-th smallest element in expected O(n) · `./dsa test 09/quickselect`

## Practice
- [ ] `sort_an_array` · Medium · solve it with each implementation above · `./dsa test 09/sort_an_array`
- [ ] `sort_colors` · Medium · `./dsa test 09/sort_colors`
- [ ] `kth_largest_array` · Medium · solve with quickselect · `./dsa test 09/kth_largest_array`
- [ ] `largest_number` · Medium · `./dsa test 09/largest_number`
- [ ] `h_index` · Medium · `./dsa test 09/h_index`

## CLRS quick reference (≈85 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `mergeSort` | §2.3 (3e) / §2.3 (4e), "Designing algorithms" | MERGE and MERGE-SORT pseudocode (≈15 min) | You can write merge from memory without an off-by-one. |
| Before `quickSort` | §7.1 (3e) / §7.1 (4e), "Description of quicksort"; §7.3 (3e) / §7.3 (4e), "A randomized version of quicksort" | PARTITION (Lomuto), then random pivot choice (≈20 min). The end-of-chapter problem on Hoare partition covers the other scheme. | You can write a partition and explain why a random pivot avoids the sorted-input worst case. |
| Before `heapSort` | §6.4 (3e) / §6.4 (4e), "The heapsort algorithm" | Build a max-heap, then repeatedly extract the maximum (≈10 min) | You can write sift-down from memory. |
| Review: lower bound | §8.1 (3e) / §8.1 (4e), "Lower bounds for sorting" | The decision-tree argument, statement only (≈10 min) | You can say why any comparison sort needs Ω(n log n) comparisons. |
| After `h_index` | §8.2 (3e) / §8.2 (4e), "Counting sort"; §8.3 (3e) / §8.3 (4e), "Radix sort" | The counting array, then radix sort as repeated stable counting sorts (≈15 min) | You can explain why counting sort is stable and why radix sort needs that. |
| Before `quickselect` and `kth_largest_array` | §9.2 (3e) / §9.2 (4e), "Selection in expected linear time" | RANDOMIZED-SELECT (≈15 min) | You can explain why a random pivot makes the expected work O(n), not O(n log n). |

The default library sorts (Timsort, introsort), stability trade-offs and custom comparators are not covered by a dedicated CLRS section here; `largest_number` exercises comparators directly.

## Mastery criteria
- [ ] Merge sort and quicksort can be written from memory.
- [ ] Each algorithm's trade-offs in complexity, stability, and space can be stated.
