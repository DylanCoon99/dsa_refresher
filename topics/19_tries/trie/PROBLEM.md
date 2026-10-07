# Trie (Prefix Tree)
**Topic:** 19 Tries · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Implement Trie (Prefix Tree)" (title kept for cross-reference only)

## Problem
Build a `Trie` class that stores a set of words made of lowercase letters `a`-`z`:

- `insert(word)`: add `word` to the set. Inserting the same word again changes nothing.
- `search(word)`: `true` iff `word` was inserted. A string that is only a prefix of an inserted word is **not** found until it is inserted itself.
- `startsWith(prefix)`: `true` iff at least one inserted word begins with `prefix` (every word begins with itself). `startsWith("")` is `true` as soon as one word has been inserted; its answer on a completely empty trie is not tested.

The empty string `""` is a valid word: it can be inserted, and `search("")` is `true` only after that.

The class is non-copyable (the copy operations are deleted), and its destructor must free every node you allocated. The tests create and destroy many tries, and AddressSanitizer reports a double free or use-after-free as CRASH.

Design choice to think about: a node can keep its children in a fixed array of 26 slots (O(1) child lookup, but 26 slots per node even when most are empty) or in a map (memory proportional to the children actually present, but each lookup costs more). Either passes the tests.

## Examples
- insert `"apple"` → `search("apple")` is `true`, `search("app")` is `false`, `startsWith("app")` is `true`
- then insert `"app"` → `search("app")` is `true`
- insert `""` → `search("")` is `true`

## Constraints
- Words and prefixes consist only of `a`-`z`, with length 0 to 100.
- Total length of all inserted words ≤ 2·10⁶, and at most 3·10⁵ calls per test (these limits are chosen for this exercise; the tests stay well inside them).

## Target
Time: O(L) per operation for a word of length L · Space: O(total inserted characters) nodes

## CLRS (optional, ≈5 min)
- Ch. 12 (3e) / Ch. 12 (4e), "Binary Search Trees": only the end-of-chapter problem "Radix trees" touches tries. Read its statement. External references are usually clearer.
- Skip if: you can explain why a trie lookup costs O(length of the word) and not O(number of words).

## Mastery
Under 10 minutes from memory.

## Hints
<details><summary>Hint 1</summary>Each node represents a prefix. What do you need to store in a node to know (a) where the next letter leads and (b) whether the prefix is itself a word?</details>
<details><summary>Hint 2</summary>Can `search` and `startsWith` share one "walk down the letters" helper that differs only in what it checks at the last node?</details>
