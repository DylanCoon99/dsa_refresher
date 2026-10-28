# 16 · Dynamic Programming
Run everything: `./dsa test 16` · Status: `./dsa list 16`

For every exercise, write the state, transition, base cases and evaluation order as a comment **before** coding.

## Diagnostic
Attempt cold (≤ 40 min each): `decode_ways`, `edit_distance`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] The two prerequisite properties: optimal substructure and overlapping subproblems.
- [ ] The procedure: define the state, define the transition, set the base cases, and determine the evaluation order.
- [ ] Top-down memoization versus bottom-up tabulation.
- [ ] Space optimization by rolling arrays.
- [ ] Pattern families: one-dimensional; grid; 0/1 and unbounded knapsack; two-sequence (LCS, edit distance); longest increasing subsequence, including the O(n log n) version; interval; bitmask; tree; state machine.

## Implement
Each one is written twice, memoized (`…Memo`) and tabulated (`…Tab`); the tests run the same cases against both.
- [ ] `coin_change`: fewest coins for an amount, memoized and tabulated · `./dsa test 16/coin_change` · ⭐ interview priority
- [ ] `lcs`: longest common subsequence, memoized and tabulated · `./dsa test 16/lcs`
- [ ] `knapsack_01`: 0/1 knapsack, memoized and tabulated · `./dsa test 16/knapsack_01`

## Practice
⭐ = interview priority: do these first if you're short on time.
One-dimensional:
- [ ] `climbing_stairs` · Easy · `./dsa test 16/climbing_stairs`
- [ ] `house_robber` · Medium · `./dsa test 16/house_robber`
- [ ] `house_robber_ii` · Medium · `./dsa test 16/house_robber_ii`
- [ ] `decode_ways` · Medium · `./dsa test 16/decode_ways`
- [ ] `coin_change` · Medium · `./dsa test 16/coin_change` (same exercise as under Implement) · ⭐ interview priority
- [ ] `word_break` · Medium · `./dsa test 16/word_break` · ⭐ interview priority
- [ ] `lis` · Medium · `./dsa test 16/lis` · ⭐ interview priority

Grid and knapsack:
- [ ] `unique_paths` · Medium · `./dsa test 16/unique_paths`
- [ ] `partition_equal_subset` · Medium · `./dsa test 16/partition_equal_subset`
- [ ] `target_sum` · Medium · `./dsa test 16/target_sum`
- [ ] `coin_change_ii` · Medium · `./dsa test 16/coin_change_ii`

Two-sequence:
- [ ] `lcs` · Medium · `./dsa test 16/lcs` (same exercise as under Implement)
- [ ] `edit_distance` · Medium · `./dsa test 16/edit_distance`
- [ ] `distinct_subsequences` · Hard · `./dsa test 16/distinct_subsequences`

Other patterns:
- [ ] `stock_cooldown` · Medium · `./dsa test 16/stock_cooldown`
- [ ] `longest_palindromic_subseq` · Medium · `./dsa test 16/longest_palindromic_subseq`
- [ ] `burst_balloons` · Hard · `./dsa test 16/burst_balloons`

## CLRS quick reference (≈85 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `coin_change` | §15.1 (3e) / §14.1 (4e), "Rod cutting" | The clearest memo-versus-tab comparison (≈20 min) | You can convert a memoized recursion into a bottom-up loop (and back) without help. |
| Before the Practice problems | §15.3 (3e) / §14.3 (4e), "Elements of dynamic programming" | Optimal substructure and overlapping subproblems; highly recommended for rebuilding intuition (≈20 min) | You can say why a problem has optimal substructure and why memoization helps it. |
| Before `lcs` | §15.4 (3e) / §14.4 (4e), "Longest common subsequence" | The optimal-substructure theorem and LCS-LENGTH (≈15 min) | You can write the recurrence for `lcs(i, j)` including the case where the last characters differ. |
| Before `lis` | §15.4 (3e) / §14.4 (4e), "Longest common subsequence" | The end-of-section exercises asking for O(n²) and O(n lg n) longest monotonically increasing subsequence (≈5 min) | You can describe both approaches and what each array stores. |
| Before `knapsack_01` | §16.2 (3e) / §15.2 (4e), "Elements of the greedy strategy" | The 0-1 versus fractional knapsack contrast (≈10 min) | You can give a tiny instance where taking the best value-per-weight item first is wrong for 0/1 knapsack. |
| Before `edit_distance` | Ch. 15 (3e) / Ch. 14 (4e), "Dynamic Programming" | The end-of-chapter problem "Edit distance" (≈10 min) | You can write the recurrence for `dist(i, j)` and say what each of the three operations corresponds to. |
| After `longest_palindromic_subseq` attempt | Ch. 15 (3e) / Ch. 14 (4e), "Dynamic Programming" | The end-of-chapter problem "Longest palindrome subsequence" (≈5 min) | You can state the recurrence on a substring `s[i..j]` and its base cases. |

## Mastery criteria
- [ ] The state and recurrence can be written down before coding.
- [ ] New problems can be classified into a known pattern family.
- [ ] A memoized solution can be converted to a tabulated one.
