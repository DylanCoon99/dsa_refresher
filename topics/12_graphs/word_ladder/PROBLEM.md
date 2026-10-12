# Word Ladder
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Word Ladder" (title kept for cross-reference only)

## Problem
A **ladder** from `beginWord` to `endWord` is a sequence of words that starts at `beginWord` and
ends at `endWord`, where each word differs from the previous one in **exactly one letter**, and
every word after `beginWord` is in `wordList`. (`beginWord` itself does not have to be in the
list.) Return the number of words in the **shortest** ladder, counting both `beginWord` and
`endWord`. Return `0` if there is no ladder, which includes the case where `endWord` is not in
`wordList`. The input never has `beginWord == endWord`.

## Examples
- `"hit" → "cog"`, list `{"hot","dot","dog","lot","log","cog"}` → `5` (`hit, hot, dot, dog, cog`)
- `"hit" → "cog"`, list `{"hot","dot","dog","lot","log"}` → `0` (`"cog"` is not in the list)
- `"a" → "c"`, list `{"a","b","c"}` → `2`

## Constraints
- All words are non-empty, lowercase, and have the same length L, 1 ≤ L ≤ 10.
- 1 ≤ wordList.size() ≤ 5000; the words in the list are distinct.
- `beginWord != endWord`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n · L²) · Space: O(n · L²) · Where: n = number of words in the list, L = word length.

The large test (5000 words of length 5) rejects comparing every pair of words to find neighbors
(O(n² · L)). Instead, file each word under its "wildcard" patterns (the word with one letter
replaced by `*`); two words are one letter apart exactly when they share a pattern.

## Hints
<details><summary>Hint 1</summary>Treat each word as a vertex and connect words that differ in one letter. You want a shortest path in an unweighted graph: which traversal gives that?</details>
<details><summary>Hint 2</summary>Comparing every word with every other is slow. If you replace one letter of a word with a wildcard, which words land under the same pattern?</details>
