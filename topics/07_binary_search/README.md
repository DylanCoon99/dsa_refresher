# 07 · Binary Search
Run everything: `./dsa test 07` · Status: `./dsa list 07`

## Diagnostic
Attempt cold (≤ 40 min each): `koko_bananas`, `search_rotated`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] The standard search on a sorted array.
- [ ] Lower-bound and upper-bound variants.
- [ ] Overflow-safe midpoint computation.
- [ ] Loop invariants.
- [ ] Searching rotated arrays.
- [ ] **Binary search on the answer:** searching a monotonic predicate over a value range.

## Implement
- [ ] `bounds`: `lowerBound` and `upperBound`, iterative, with the loop invariant written as a comment · `./dsa test 07/bounds`

## Practice
- [ ] `binary_search` · Easy · `./dsa test 07/binary_search`
- [ ] `search_2d_matrix` · Medium · `./dsa test 07/search_2d_matrix`
- [ ] `koko_bananas` · Medium · `./dsa test 07/koko_bananas`
- [ ] `find_min_rotated` · Medium · `./dsa test 07/find_min_rotated`
- [ ] `search_rotated` · Medium · `./dsa test 07/search_rotated`
- [ ] `time_map` · Medium · `./dsa test 07/time_map`
- [ ] `median_two_sorted` · Hard · `./dsa test 07/median_two_sorted`

## CLRS quick reference (≈15 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `bounds` | §2.1 (3e) / §2.1 (4e), "Insertion sort" | Only the loop-invariant discussion: initialization, maintenance, termination (≈10 min) | You can state your loop's invariant precisely. |
| After `binary_search` | §2.3 (3e) / §2.3 (4e), "Designing algorithms" | The end-of-section exercise on binary search (≈5 min) | You can explain why the search range halves each step. |

Binary search appears in CLRS only as that end-of-section exercise. Rotated arrays and binary search on the answer are not covered; use the PROBLEM.md hints.

## Mastery criteria
- [ ] Off-by-one errors no longer occur.
- [ ] Problems phrased as "minimize the maximum" or "find the smallest value such that…" are recognized as binary search on the answer.
