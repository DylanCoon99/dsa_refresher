# 15 · Backtracking
Run everything: `./dsa test 15` · Status: `./dsa list 15`

## Diagnostic
Attempt cold (≤ 40 min each): `combination_sum_ii`, `word_search`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] The choose–explore–unchoose template.
- [ ] State representation.
- [ ] Pruning.
- [ ] Handling duplicates by sorting and skipping.
- [ ] The complexity of generating subsets (2ⁿ) and permutations (n!).

## Implement
- [ ] `backtracking_templates`: generic templates for generating subsets, permutations, and combinations · `./dsa test 15/backtracking_templates`

## Practice
⭐ = interview priority: do these first if you're short on time.
- [ ] `subsets` · Medium · `./dsa test 15/subsets` · ⭐ interview priority
- [ ] `subsets_ii` · Medium · `./dsa test 15/subsets_ii`
- [ ] `permutations` · Medium · `./dsa test 15/permutations`
- [ ] `combination_sum` · Medium · `./dsa test 15/combination_sum` · ⭐ interview priority
- [ ] `combination_sum_ii` · Medium · `./dsa test 15/combination_sum_ii`
- [ ] `word_search` · Medium · `./dsa test 15/word_search` · ⭐ interview priority
- [ ] `palindrome_partitioning` · Medium · `./dsa test 15/palindrome_partitioning`
- [ ] `n_queens` · Hard · `./dsa test 15/n_queens`

## CLRS quick reference
Backtracking is not directly covered by CLRS, so there is no reading list for this topic.

## Mastery criteria
- [ ] Any enumeration problem can be expressed with the template.
- [ ] Duplicate results are avoided reliably.
