# 13 · Union-Find (Disjoint Sets)
Run everything: `./dsa test 13` · Status: `./dsa list 13`

## Diagnostic
Attempt cold (≤ 40 min each): `redundant_connection`, `accounts_merge`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Find and union.
- [ ] Path compression.
- [ ] Union by rank or size.
- [ ] The inverse Ackermann bound.
- [ ] When union-find is preferable to DFS: incremental connectivity and cycle detection during edge insertion.

## Implement
- [ ] `union_find`: union-find with path compression and union by rank or size · `./dsa test 13/union_find`

## Practice
- [ ] `count_components` · Medium · `./dsa test 13/count_components`
- [ ] `redundant_connection` · Medium · `./dsa test 13/redundant_connection`
- [ ] `accounts_merge` · Medium · `./dsa test 13/accounts_merge`
- [ ] `number_of_provinces` · Medium · `./dsa test 13/number_of_provinces`

## CLRS quick reference (≈25 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `union_find` | §21.3 (3e) / §19.3 (4e), "Disjoint-set forests" | The two heuristics (union by rank, path compression) and the pseudocode; skip the amortized analysis (≈15 min) | You can write `find` and `unite` with both heuristics without looking. |
| Before `count_components` | §21.1 (3e) / §19.1 (4e), "Disjoint-set operations" | The connected-components application (≈5 min) | You can explain how union-find counts the components of a graph given its edges. |
| After `union_find` | §21.4 (3e) / §19.4 (4e), "Analysis of union by rank with path compression" | The theorem statement only, to see where the inverse Ackermann bound comes from; skip the proof (≈5 min) | You can state the amortized cost per operation and say that α(n) is at most 4 for any practical n. |

## Mastery criteria
- [ ] The structure can be written from memory in under five minutes.
- [ ] Its use cases can be stated.
