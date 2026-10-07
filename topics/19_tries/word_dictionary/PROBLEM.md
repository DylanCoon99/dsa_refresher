# Word Dictionary with Wildcards
**Topic:** 19 Tries · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Design Add and Search Words Data Structure" (title kept for cross-reference only)

## Problem
Design a `WordDictionary` that supports two operations:

- `addWord(word)`: store a lowercase word.
- `search(pattern)`: return `true` iff some stored word *matches* the pattern. A word matches when it has exactly the pattern's length and, at every position, the pattern character is either the same letter or `.`. A `.` stands for any single letter, never for "nothing" and never for more than one letter.

Searching an empty dictionary returns `false`.

## Examples
After adding `"bad"`, `"dad"`, `"mad"`:
- `search("pad")` → `false` (no word starts with `p`)
- `search("bad")` → `true`
- `search(".ad")` → `true` (matches `bad`, `dad` and `mad`)
- `search("b..")` → `true` (matches `bad`)

## Constraints
- Words: lowercase `a`-`z`, length 1 to 25. Patterns: `a`-`z` and `.`, length 1 to 25.
- At most 5·10⁴ calls per test (invented limit for this exercise; the tests stay inside it).

## Target
Time: `addWord` O(L). `search` is O(L) when the pattern has no dots; with dots it may visit many nodes (worst case about the number of trie nodes of depth at most L). Space: O(total characters)

## Hints
<details><summary>Hint 1</summary>A plain trie handles the literal letters. What should the search do at a node when the next pattern character is `.`?</details>
<details><summary>Hint 2</summary>If a `.` means "any child", can you write the search as a recursion over (node, position in the pattern) that returns true as soon as one branch succeeds?</details>
