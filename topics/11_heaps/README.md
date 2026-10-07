# 11 · Heaps and Priority Queues
Run everything: `./dsa test 11` · Status: `./dsa list 11`

## Diagnostic
Attempt cold (≤ 40 min each): `k_closest_points`, `median_finder`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Binary heap array representation and index arithmetic.
- [ ] Sift-up and sift-down.
- [ ] O(n) heapify, including why it is linear.
- [ ] Min-heaps versus max-heaps, and the negation technique in Python's `heapq`.
- [ ] Top-k patterns.
- [ ] Two-heap median maintenance.
- [ ] Merging k sorted sequences.

## Implement
- [ ] `min_heap`: an array-backed binary min-heap with push, pop, top and an O(n) heapify constructor · `./dsa test 11/min_heap`

## Practice
- [ ] `kth_largest_stream` · Easy · `./dsa test 11/kth_largest_stream`
- [ ] `last_stone_weight` · Easy · `./dsa test 11/last_stone_weight`
- [ ] `k_closest_points` · Medium · `./dsa test 11/k_closest_points`
- [ ] `task_scheduler` · Medium · `./dsa test 11/task_scheduler`
- [ ] `median_finder` · Hard · `./dsa test 11/median_finder`

## CLRS quick reference (≈30 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `min_heap` | §6.1–6.2 (3e) / §6.1–6.2 (4e), "Heaps" and "Maintaining the heap property" | The array layout, index arithmetic, and MAX-HEAPIFY (≈10 min) | You can write sift-down from memory and give the parent and child indices. |
| Before `min_heap` | §6.3 (3e) / §6.3 (4e), "Building a heap" | BUILD-MAX-HEAP and the argument that it runs in O(n) (≈10 min) | You can explain why bottom-up heapify is linear. |
| Before `median_finder` | §6.5 (3e) / §6.5 (4e), "Priority queues" | The priority-queue operations and how a heap implements them (≈10 min) | You can say which heap operations a problem needs and what each costs. |

## Mastery criteria
- [ ] It can be decided quickly whether a problem calls for a heap, sorting, or quickselect, and the choice can be justified.
