# Min Stack
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Min Stack" (title kept for cross-reference only)

## Problem
Implement a stack of `int` named `MinStack` that can also report its smallest element at any
time. All four operations must run in **O(1)** time.

- `void push(int val)`: place `val` on top.
- `void pop()`: remove the top element.
- `int top() const`: return the top element.
- `int getMin() const`: return the smallest element currently in the stack.

`pop`, `top` and `getMin` are never called on an empty stack. Duplicate values are allowed,
and `getMin` must still be right after the top copy of the minimum is popped.

## Examples
- `push(-2), push(0), push(-3)`: `getMin()` → `-3`; `pop()`; `top()` → `0`; `getMin()` → `-2`
- `push(0), push(1), push(0)`: `getMin()` → `0`; `pop()`; `getMin()` → `0` (the other 0 remains)
- `push(5)`: `top()` → `5`, `getMin()` → `5`

## Constraints
- Up to 10⁵ operations per test (the large test pushes 10⁵ values, then calls `getMin` 10⁵ times).
- −2³¹ ≤ val ≤ 2³¹ − 1 (any `int`, including `INT_MIN`).

## Target
Time: O(1) per operation · Space: O(n)

## Hints
<details><summary>Hint 1</summary>When you pop an element, what is the minimum of everything that remains? Could that value have been known at the moment the element below was pushed?</details>
<details><summary>Hint 2</summary>What if every stack entry also remembered the minimum of the stack up to and including itself? Which duplicate-minimum situation does this handle for free?</details>
