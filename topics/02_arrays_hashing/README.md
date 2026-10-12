# 02 · Arrays and Hashing
Run everything: `./dsa test 02` · Status: `./dsa list 02`

## Diagnostic
Attempt cold (≤ 40 min each): `group_anagrams`, `product_except_self`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Dynamic array growth, contiguous memory, and cache locality.
- [ ] Hash table internals: hash functions, chaining versus open addressing, load factor and resizing, worst-case degradation.
- [ ] Hash sets versus hash maps, and frequency counting.
- [ ] String immutability and the cost of repeated concatenation.

## Implement
- [ ] `hash_map`: a string-to-int hash map with separate chaining and automatic resizing · `./dsa test 02/hash_map`

## Practice
- [x] `contains_duplicate` · Easy · `./dsa test 02/contains_duplicate`
- [x] `valid_anagram` · Easy · `./dsa test 02/valid_anagram`
- [x] `two_sum` · Easy · `./dsa test 02/two_sum`
- [ ] `group_anagrams` · Medium · `./dsa test 02/group_anagrams`
- [x] `top_k_frequent` · Medium · `./dsa test 02/top_k_frequent`
- [x] `product_except_self` · Medium · `./dsa test 02/product_except_self`
- [ ] `longest_consecutive` · Medium · `./dsa test 02/longest_consecutive`

## CLRS quick reference (≈50 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `hash_map` | §11.2 (3e) / §11.2 (4e), "Hash tables" | Chaining and the load factor α (≈15 min) | You can explain α and why resizing keeps operations O(1) amortized. |
| Hash functions feel like magic | §11.3 (3e) / §11.3 (4e), "Hash functions" | Division and multiplication methods only (≈10 min) | You can say what makes a hash function good and compute `k mod m`. |
| Chaining vs open addressing | §11.4 (3e) / §11.4 (4e), "Open addressing" | Intro and linear probing (≈10 min) | You can explain why open addressing needs a lower load factor than chaining. |
| Review: dynamic arrays | §17.4 (3e) / §16.4 (4e), "Dynamic tables" | Table expansion (≈15 min) | You can show doubling gives O(1) amortized append. |

## Mastery criteria
- [ ] Hashing can be used to reduce O(n²) pair searches to O(n) without prompting.
- [ ] Collision handling and resizing can be explained.
