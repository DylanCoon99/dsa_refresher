# 19 · Tries
Run everything: `./dsa test 19` · Status: `./dsa list 19`

This is an Advanced topic: begin it after the core topics are complete.

## Diagnostic
Attempt cold (≤ 40 min each): `word_dictionary`, `word_search_ii`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Node structure using a child map or a fixed-size array.
- [ ] Insert, search, and prefix search.
- [ ] Wildcard matching via DFS.
- [ ] Pruning a trie during backtracking.

## Implement
- [ ] `trie`: a trie supporting insert, search, and `startsWith` (also the "Implement Trie (Prefix Tree)" practice problem) · `./dsa test 19/trie`

## Practice
- [ ] `trie` · Medium · `./dsa test 19/trie` (Implement Trie (Prefix Tree); the same exercise as above)
- [ ] `word_dictionary` · Medium · `./dsa test 19/word_dictionary`
- [ ] `word_search_ii` · Hard · `./dsa test 19/word_search_ii`

## CLRS quick reference (≈5 min, all optional)
CLRS covers tries only through one end-of-chapter problem; prefer external references and the hints in each PROBLEM.md.

| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| With `trie` | Ch. 12 (3e) / Ch. 12 (4e), "Binary Search Trees": end-of-chapter problem "Radix trees" | The problem statement only (≈5 min) | You can explain why a trie lookup costs O(length of the word) rather than O(number of words). |

## Mastery criteria
- [ ] A trie can be implemented in under ten minutes and combined with DFS.
