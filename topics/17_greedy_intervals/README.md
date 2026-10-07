# 17 · Greedy Algorithms and Intervals
Run everything: `./dsa test 17` · Status: `./dsa list 17`

Interval conventions differ by exercise, and each PROBLEM.md states its own. Closed (touching intervals overlap): `merge_intervals`, `insert_interval`, `min_arrows`. Half-open (touching intervals do not overlap): `max_overlap`, `non_overlapping_intervals`, `meeting_rooms_ii`, `car_pooling`.

For every greedy exercise, write one sentence on why the greedy choice is safe (the exchange argument) **before** coding.

## Diagnostic
Attempt cold (≤ 40 min each): `non_overlapping_intervals`, `gas_station`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] The greedy-choice property, and the exchange argument for proving correctness.
- [ ] Common counterexamples where a greedy approach fails.
- [ ] Interval problems: sorting by start or end; merging; removing overlaps; counting the maximum concurrent intervals (sweep line, or a min-heap of end times).

## Implement
- [ ] `merge_intervals`: an interval-merging routine (same exercise as under Practice) · `./dsa test 17/merge_intervals`
- [ ] `max_overlap`: a sweep-line computation of maximum overlap · `./dsa test 17/max_overlap`

## Practice
- [ ] `jump_game` · Medium · `./dsa test 17/jump_game`
- [ ] `jump_game_ii` · Medium · `./dsa test 17/jump_game_ii`
- [ ] `gas_station` · Medium · `./dsa test 17/gas_station`
- [ ] `partition_labels` · Medium · `./dsa test 17/partition_labels`
- [ ] `merge_intervals` · Medium · `./dsa test 17/merge_intervals` (same exercise as under Implement)
- [ ] `insert_interval` · Medium · `./dsa test 17/insert_interval`
- [ ] `non_overlapping_intervals` · Medium · `./dsa test 17/non_overlapping_intervals`
- [ ] `min_arrows` · Medium · `./dsa test 17/min_arrows`
- [ ] `meeting_rooms_ii` · Medium · `./dsa test 17/meeting_rooms_ii` (a premium problem on LeetCode; `car_pooling` is the free alternative)
- [ ] `car_pooling` · Medium · `./dsa test 17/car_pooling`

## CLRS quick reference (≈50 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `non_overlapping_intervals` | §16.1 (3e) / §15.1 (4e), "An activity-selection problem" | The greedy-choice theorem statement (≈15 min) | You can state why sorting by end time is safe. |
| After `max_overlap` | §16.1 (3e) / §15.1 (4e), "An activity-selection problem" | The end-of-section exercise on scheduling activities among the fewest lecture halls (interval-graph coloring) (≈5 min) | You can explain why the number of lecture halls needed equals the maximum overlap. |
| When the greedy-choice idea feels shaky | §16.2 (3e) / §15.2 (4e), "Elements of the greedy strategy" | The greedy-choice property and optimal substructure (≈15 min) | You can say what the greedy-choice property is and how it differs from optimal substructure. |
| Review only | §16.3 (3e) / §15.3 (4e), "Huffman codes" | The algorithm and the greedy lemma statement (≈15 min) | You can describe which two nodes Huffman merges at each step and why that is safe. |

## Mastery criteria
- [ ] A brief argument can be given for why a greedy choice is safe, or a counterexample found when it is not.
