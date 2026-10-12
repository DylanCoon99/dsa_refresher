# Word Search II
**Topic:** 19 Tries · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Word Search II" (title kept for cross-reference only)

## Problem
You are given a grid of lowercase letters `board` and a list of lowercase `words`. Return every word from the list that can be spelled on the board: start at any cell, and move one step at a time to a horizontally or vertically adjacent cell (no diagonals). A single cell may be used **at most once** within one word. (Different words are independent, so they may share cells.)

- Each qualifying word appears **once** in the result, even if it can be traced in several ways or is repeated in `words`.
- The result may be in any order.
- The board is passed by value, so you may modify your copy (for example to mark visited cells).

## Examples
- `board = {{o,a,a,n},{e,t,a,e},{i,h,k,r},{i,f,l,v}}`, `words = {"oath","pea","eat","rain"}` → `{"oath", "eat"}` (any order)
- `board = {{a,b},{c,d}}`, `words = {"abcb"}` → `{}` (spelling it would reuse the `b`)
- `board = {{a}}`, `words = {"a","aa"}` → `{"a"}`

## Constraints
- 1 ≤ rows, cols ≤ 12
- 1 ≤ words.size() ≤ 3·10⁴; each word has length 1 to 10; letters are `a`-`z`; `words` may contain duplicates
- (The word count and the 12×12 limit are chosen for this exercise; the tests stay inside them.)

## Target
Time: roughly O(cells · 4 · 3^(L-1)) in the worst case, but only paths that are prefixes of some word are explored · Space: O(total characters in words) for the trie · Where: cells = rows × columns of the board, L = length of the longest word.

## Hints
<details><summary>Hint 1</summary>Searching the board once per word repeats the same path exploration thousands of times. How could one board DFS test every word at the same time?</details>
<details><summary>Hint 2</summary>Put all the words in a trie and walk the trie and the board together, stopping as soon as the current path is not a prefix of any word. Once a word is found, delete its trie node (and any ancestors left with no children and no word) so that the same dead branch is never explored again.</details>
