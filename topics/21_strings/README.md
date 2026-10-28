# 21 · String Algorithms
Run everything: `./dsa test 21` · Status: `./dsa list 21`

This is an Advanced topic: begin it after the core topics are complete.

## Diagnostic
Attempt cold (≤ 40 min each): `longest_palindromic_substring`, `strstr_kmp`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Knuth-Morris-Pratt and its prefix function.
- [ ] Rabin-Karp and rolling hashes.
- [ ] The Z-algorithm.
- [ ] Expand-around-center for palindromes. Manacher's algorithm is optional.

## Implement
- [ ] `kmp`: the KMP prefix function and matcher · `./dsa test 21/kmp`
- [ ] `rolling_hash`: a polynomial rolling hash with O(1) substring queries · `./dsa test 21/rolling_hash`

## Practice
⭐ = interview priority: do these first if you're short on time.
- [ ] `strstr_kmp` · Easy · `./dsa test 21/strstr_kmp`
- [ ] `repeated_string_match` · Medium · `./dsa test 21/repeated_string_match`
- [ ] `longest_palindromic_substring` · Medium · `./dsa test 21/longest_palindromic_substring` · ⭐ interview priority
- [ ] `palindromic_substrings` · Medium · `./dsa test 21/palindromic_substrings` · ⭐ interview priority
- [ ] `longest_duplicate_substring` · Hard · `./dsa test 21/longest_duplicate_substring`

## CLRS quick reference (≈40 min, all optional)
The Z-algorithm and Manacher's algorithm are not in CLRS.

| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| With `strstr_kmp` | §32.1 (3e) / §32.1 (4e), "The naive string-matching algorithm" | The naive matcher (≈5 min) | You can explain why the naive method does about n·m comparisons on `aaaa…a` against `aaa…ab`. |
| With `rolling_hash` | §32.2 (3e) / §32.2 (4e), "The Rabin-Karp algorithm" | The rolling update formula (≈15 min) | You can explain how to drop the leading character of a window and append a new one in O(1). |
| With `kmp` | §32.4 (3e) / §32.4 (4e), "The Knuth-Morris-Pratt algorithm" | COMPUTE-PREFIX-FUNCTION and KMP-MATCHER (≈20 min) | You can explain what π[i] means and why the matcher is linear. |

## Mastery criteria
- [ ] The prefix function can be explained.
- [ ] KMP can be implemented with brief reference.
