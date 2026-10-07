# 20 · Range Query Structures
Run everything: `./dsa test 20` · Status: `./dsa list 20`

This is an Advanced topic: begin it after the core topics are complete.

## Diagnostic
Attempt cold (≤ 40 min each): `range_sum_mutable`, `my_calendar_i`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Segment trees: build, point update, range query, and lazy propagation.
- [ ] Fenwick trees (binary indexed trees).
- [ ] When a prefix-sum array suffices and when a dynamic structure is required.

## Implement
- [ ] `fenwick_tree`: a Fenwick tree with point add, prefix sum and range sum · `./dsa test 20/fenwick_tree`
- [ ] `segment_tree`: a segment tree with range-sum queries and point assignment · `./dsa test 20/segment_tree`

## Practice
- [ ] `range_sum_mutable` · Medium · `./dsa test 20/range_sum_mutable`
- [ ] `count_smaller_after_self` · Hard · `./dsa test 20/count_smaller_after_self`
- [ ] `my_calendar_i` · Medium · `./dsa test 20/my_calendar_i`

## CLRS quick reference (≈40 min, all optional)
Fenwick trees and segment trees are not in CLRS; the rows below cover the related augmented-tree ideas.

| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| With `segment_tree` | §14.2 (3e) / §17.2 (4e), "How to augment a data structure" | The section intro (≈10 min) | You can explain what summary each node stores and how an update re-derives it from its children. |
| With `count_smaller_after_self` | §14.1 (3e) / §17.1 (4e), "Dynamic order statistics" | OS-RANK (≈15 min) | You can explain how subtree sizes let a tree answer a rank query in O(log n). |
| With `my_calendar_i` | §14.3 (3e) / §17.3 (4e), "Interval trees" | INTERVAL-SEARCH (≈15 min) | You can explain why only the neighbours of the new start need checking. |

## Mastery criteria
- [ ] A Fenwick tree can be written from memory.
- [ ] A segment tree can be written with brief reference.
