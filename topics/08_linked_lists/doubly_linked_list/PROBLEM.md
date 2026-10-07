# Doubly Linked List
**Topic:** 08 Linked Lists · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement `DoublyLinkedList`, a doubly linked list of `int` with these members:

- `DoublyLinkedList()` / `~DoublyLinkedList()`: create an empty list; the destructor releases every node you allocated. Copying is deleted.
- `void pushFront(int v)` / `void pushBack(int v)`: insert at either end.
- `int popFront()` / `int popBack()`: remove an end element and return its value.
- `int front() const` / `int back() const`: return an end value without removing it.
- `bool remove(int v)`: delete the **first** (front-most) element equal to `v`; return `true` if one was found, `false` otherwise.
- `std::size_t size() const` / `bool empty() const`.
- `std::vector<int> toVector() const`: the values from front to back.

`popFront`, `popBack`, `front` and `back` on an empty list must throw `std::out_of_range`.

**Use sentinel nodes** (a dummy head and/or tail that never holds a value) so that insert and delete need no head/tail special cases. The tests cannot see how you store your nodes, so this requirement is not enforced; it is the point of the exercise.
The tests also cannot detect leaked memory (LeakSanitizer is unavailable on macOS arm64). They do detect a double free or use-after-free in your destructor and `remove`.

## Examples
- `pushBack(1), pushBack(2), pushFront(0)` → `toVector()` is `{0, 1, 2}`
- from `{0, 1, 2}`: `popFront()` → `0`, `popBack()` → `2`, leaving `{1}`
- from `{5, 7, 5}`: `remove(5)` → `true`, leaving `{7, 5}`; `remove(9)` → `false`

## Constraints
- Up to 10⁵ operations per test (invented limit; the randomized test uses 10⁵ mixed operations).
- Any `int` values.

## Target
Time: O(1) per operation except `remove` and `toVector`, which are O(n) · Space: O(n)

## CLRS (optional, ≈15 min)
- §10.2 (3e) / §10.2 (4e), "Linked lists": read LIST-INSERT and LIST-DELETE, then the sentinel versions.
- Skip if: you can write delete without any head/tail special case.

## Hints
<details><summary>Hint 1</summary>If the list always has a dummy node at each end, can every real node be assumed to have a non-null prev and next?</details>
<details><summary>Hint 2</summary>Which single helper (unlink a node, insert before a node) can all of pushFront, pushBack, popFront, popBack and remove be written with?</details>
