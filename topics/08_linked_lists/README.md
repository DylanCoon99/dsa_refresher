# 08 · Linked Lists
Run everything: `./dsa test 08` · Status: `./dsa list 08`

## Diagnostic
Attempt cold (≤ 40 min each): `reorder_list`, `remove_nth_from_end`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Singly and doubly linked lists.
- [ ] Sentinel (dummy) nodes.
- [ ] Iterative and recursive reversal.
- [ ] Merging sorted lists.
- [ ] Fast and slow pointers: cycle detection with Floyd's algorithm, and finding the middle node.
- [ ] The LRU cache design, which combines a hash map with a doubly linked list.

## Implement
- [ ] `doubly_linked_list`: a doubly linked list with sentinel nodes · `./dsa test 08/doubly_linked_list`
- [ ] `lru_cache`: an LRU cache with O(1) `get` and `put` (also a Practice problem below) · `./dsa test 08/lru_cache`

## Practice
- [ ] `reverse_linked_list` · Easy · `./dsa test 08/reverse_linked_list`
- [ ] `merge_two_lists` · Easy · `./dsa test 08/merge_two_lists`
- [ ] `linked_list_cycle` · Easy · `./dsa test 08/linked_list_cycle`
- [ ] `reorder_list` · Medium · `./dsa test 08/reorder_list`
- [ ] `remove_nth_from_end` · Medium · `./dsa test 08/remove_nth_from_end`
- [ ] `copy_random_list` · Medium · `./dsa test 08/copy_random_list`
- [ ] `lru_cache` · Medium · `./dsa test 08/lru_cache`
- [ ] `merge_k_lists` · Hard · `./dsa test 08/merge_k_lists`

## CLRS quick reference (≈35 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `doubly_linked_list` | §10.2 (3e) / §10.2 (4e), "Linked lists" | LIST-INSERT and LIST-DELETE, then the sentinel versions (≈15 min) | You can write delete without any head/tail special case. |
| Before `lru_cache` | §10.2 (3e) / §10.2 (4e), "Linked lists" | Re-read the sentinel LIST-DELETE; moving a node to the front is a delete plus an insert (≈10 min) | You can splice a node out and re-insert it at the front without any head/tail special case. |
| Before `merge_k_lists` | §6.5 (3e) / §6.5 (4e), "Priority queues" | What a priority queue supports and its heap implementation (≈10 min) | You can explain why a heap of k list heads yields the next smallest value in O(log k). |

Floyd's cycle detection is not in CLRS. Use the PROBLEM.md hints, or a problem editorial for "linked list cycle".

## Mastery criteria
- [ ] Pointer manipulation is performed correctly on the first attempt, including at the head and tail boundaries.
