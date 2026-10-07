# Evaluate Reverse Polish Notation
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Evaluate Reverse Polish Notation" (title kept for cross-reference only)

## Problem
`tokens` is an arithmetic expression in postfix (reverse Polish) form. Each token is either an
integer written in decimal (possibly negative, such as `"-11"`) or one of the operators
`"+"`, `"-"`, `"*"`, `"/"`. An operator applies to the two values before it: the earlier one
is the left operand and the later one is the right operand. Return the value of the expression.

Division truncates toward zero (`7 / -2` is `-3`). The expression is always valid, never divides
by zero, and every intermediate result fits in a 32-bit `int`.

## Examples
- `{"2", "1", "+", "3", "*"}` → `9`; `(2 + 1) * 3`
- `{"4", "13", "5", "/", "+"}` → `6`; `4 + (13 / 5)`
- `{"6", "-132", "/"}` → `0`; `6 / -132` truncates to 0

## Constraints
- 1 ≤ tokens.size() ≤ 10⁴
- Numbers fit in `int`; all intermediate results fit in `int`.

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>When you reach an operator, which two values does it need? Where were they last seen?</details>
<details><summary>Hint 2</summary>Which operand comes off the stack first, and does that matter for `-` and `/`?</details>
