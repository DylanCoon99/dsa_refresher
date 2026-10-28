# 05 · Prefix Sums and Difference Arrays
Run everything: `./dsa test 05` · Status: `./dsa list 05`

## Diagnostic
Attempt cold (≤ 40 min each): `subarray_sum_k`, `range_sum_query_2d`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] One-dimensional and two-dimensional prefix sums.
- [ ] Combining prefix sums with a hash map to count subarrays that hit a target sum.
- [ ] Difference arrays for O(1) range updates.

## Implement
- [ ] `prefix_sum_2d`: a 2-D prefix sum structure that answers rectangle-sum queries in O(1) · `./dsa test 05/prefix_sum_2d`

## Practice
⭐ = interview priority: do these first if you're short on time.
- [ ] `range_sum_query` · Easy · `./dsa test 05/range_sum_query`
- [ ] `range_sum_query_2d` · Medium · `./dsa test 05/range_sum_query_2d`
- [ ] `subarray_sum_k` · Medium · `./dsa test 05/subarray_sum_k` · ⭐ interview priority
- [ ] `continuous_subarray_sum` · Medium · `./dsa test 05/continuous_subarray_sum` · ⭐ interview priority
- [ ] `corporate_flight_bookings` · Medium · `./dsa test 05/corporate_flight_bookings`

## CLRS quick reference
Not directly covered by CLRS.

## Mastery criteria
- [ ] It can be recognized when a running-sum transformation converts a subarray problem into a lookup problem.
