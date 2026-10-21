# 04 · Sliding Window
Run everything: `./dsa test 04` · Status: `./dsa list 04`

## Diagnostic
Attempt cold (≤ 40 min each): `longest_substring_no_repeat`, `char_replacement`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Fixed-size windows.
- [ ] Variable-size windows: expand on the right, contract on the left while a constraint is violated.
- [ ] Maintaining window state with counters, hash maps, or a deque.

## Implement
- [ ] `window_template`: a reusable variable-window template that maintains a frequency map · `./dsa test 04/window_template`

## Practice
- [x] `best_time_stock` · Easy · `./dsa test 04/best_time_stock`
- [ ] `longest_substring_no_repeat` · Medium · `./dsa test 04/longest_substring_no_repeat`
- [ ] `char_replacement` · Medium · `./dsa test 04/char_replacement`
- [ ] `permutation_in_string` · Medium · `./dsa test 04/permutation_in_string`
- [ ] `min_window_substring` · Hard · `./dsa test 04/min_window_substring`
- [ ] `sliding_window_max` · Hard · `./dsa test 04/sliding_window_max`

## CLRS quick reference
Not directly covered by CLRS.

## Mastery criteria
- [ ] Any "longest/shortest contiguous subarray or substring satisfying a condition" problem can be solved in O(n) using the template.
