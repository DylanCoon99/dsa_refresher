# Group Anagrams
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Group Anagrams" (title kept for cross-reference only)

## Problem
Given a list of words `strs`, partition them into groups so that two words are in the same
group exactly when they are anagrams of each other. Return the groups as a list of lists.
The order of the groups, and the order of words inside a group, do not matter. Every input
word appears in exactly one group; duplicate words stay duplicated.

## Examples
- `strs = {"eat", "tea", "tan", "ate", "nat", "bat"}` → `{{"eat","tea","ate"}, {"tan","nat"}, {"bat"}}` (any order)
- `strs = {""}` → `{{""}}`
- `strs = {"a"}` → `{{"a"}}`

## Constraints
- n ≤ 10⁴ words.
- Each word has length ≤ 100 and uses lowercase letters (a word may be empty).

## Target
Time: O(n · L log L), or O(n · L) with letter counts · Space: O(n · L)

## Hints
<details><summary>Hint 1</summary>Two words are anagrams exactly when they share some canonical form. What could that form be?</details>
<details><summary>Hint 2</summary>If every word is mapped to its canonical form (for example its letters sorted), can a hash map from that form to a list of words do the grouping in one pass?</details>
