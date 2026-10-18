# 03 · Two Pointers
Run everything: `./dsa test 03` · Status: `./dsa list 03`

## Diagnostic
Attempt cold (≤ 40 min each): `three_sum`, `container_most_water`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Opposite-direction pointers on sorted data.
- [ ] Same-direction (read/write) pointers for in-place modification.
- [ ] Fast and slow pointers. Their use for cycles is revisited in Linked Lists.

## Implement
- [ ] `dedup_sorted`: in-place deduplication of a sorted array · `./dsa test 03/dedup_sorted`
- [ ] `partition_pivot`: partition an array around a pivot, in place · `./dsa test 03/partition_pivot`

## Practice
- [x] `valid_palindrome` · Easy · `./dsa test 03/valid_palindrome`
- [x] `two_sum_ii` · Medium · `./dsa test 03/two_sum_ii`
- [ ] `three_sum` · Medium · `./dsa test 03/three_sum`
- [x] `container_most_water` · Medium · `./dsa test 03/container_most_water`
- [ ] `trapping_rain_water` · Hard · `./dsa test 03/trapping_rain_water`

## CLRS quick reference
Not directly covered by CLRS.

## Mastery criteria
- [ ] It can be recognized immediately when sorted input permits a two-pointer approach, and the reason each pointer moves can be justified.
