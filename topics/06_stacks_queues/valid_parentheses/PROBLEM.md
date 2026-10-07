# Valid Parentheses
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Valid Parentheses" (title kept for cross-reference only)

## Problem
A string `s` consists only of the characters `(`, `)`, `[`, `]`, `{` and `}`. Decide whether
it is *balanced*: every opening bracket is closed by a bracket of the **same type**, and
brackets are closed in the right order (the most recently opened one first). The empty
string is balanced.

## Examples
- `s = "()[]{}"` → `true`
- `s = "([)]"` → `false`; the `)` arrives while `[` is the most recent open bracket
- `s = "(("` → `false`; two brackets are never closed

## Constraints
- 0 ≤ |s| ≤ 10⁴ (the large nesting test uses 2·10⁴ characters)
- `s` contains only the six bracket characters

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>When a closing bracket arrives, which earlier opening bracket must it match?</details>
<details><summary>Hint 2</summary>Which structure gives you "the most recent still-open bracket" in O(1)? What must be true of it at the very end of the string?</details>
