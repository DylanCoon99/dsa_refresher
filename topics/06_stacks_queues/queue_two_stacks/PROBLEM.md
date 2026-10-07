# Queue Using Two Stacks
**Topic:** 06 Stacks, Queues, and Monotonic Structures · **Kind:** Implement · **Difficulty:** Easy

## Problem
Implement a FIFO queue of `int` named `TwoStackQueue` using **only two `std::vector<int>`
used as stacks** (`push_back`, `pop_back`, `back`, `empty`, `size`). Do not use any other
container and do not index into the vectors.

- `void push(int x)`: add `x` at the back of the queue.
- `int pop()`: remove and return the front element. Throws `std::out_of_range` if the queue is empty.
- `int peek()`: return the front element without removing it. Throws `std::out_of_range` if the queue is empty.
- `bool empty() const`: true when the queue holds no elements.
- `std::size_t size() const`: number of elements in the queue.

Every operation must be **amortized O(1)**: any sequence of n operations costs O(n) in total.

## Examples
- `push(1), push(2), peek()` → `1`; the oldest element is at the front.
- `push(1), push(2), pop(), push(3), pop(), pop()` → `1, 2, 3`
- A new `TwoStackQueue`: `pop()` and `peek()` throw `std::out_of_range`.

## Constraints
- Up to 10⁶ operations in total.
- −2³¹ ≤ x ≤ 2³¹ − 1 (any `int`).

## Target
Time: O(1) amortized per operation · Space: O(n)

## CLRS (optional, ≈20 min)
- §10.1 (3e) / §10.1 (4e), "Stacks and queues" / "Simple array-based data structures: arrays, matrices, stacks, queues": read the STACK and ENQUEUE/DEQUEUE pseudocode (≈10 min). An end-of-section exercise asks for exactly this design.
- §17.1 (3e) / §16.1 (4e), "Aggregate analysis": read the stack-operations example for the amortized argument (≈10 min).
- Skip if: you can explain why each element is moved at most twice.

## Hints
<details><summary>Hint 1</summary>One stack receives pushes. When you need the front element, the oldest item sits at the bottom of that stack. What would reversing the stack do to the order?</details>
<details><summary>Hint 2</summary>Do you need to move elements on every pop, or only when the stack you pop from has run dry? Count how many times a single element can ever be moved.</details>
