# 06 · Stacks, Queues, and Monotonic Structures
Run everything: `./dsa test 06` · Status: `./dsa list 06`

## Diagnostic
Attempt cold (≤ 40 min each): `daily_temperatures`, `eval_rpn`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Stack (LIFO) and queue (FIFO) semantics and their array or linked implementations.
- [ ] Deques.
- [ ] Monotonic stacks for "next greater/smaller element" problems.
- [ ] Monotonic deques for sliding-window extrema.
- [ ] Expression parsing.

## Implement
- [ ] `queue_two_stacks`: a FIFO queue built from two stacks, with an amortized O(1) analysis · `./dsa test 06/queue_two_stacks`
- [ ] `min_stack`: a stack that reports its minimum in O(1) (also a Practice problem below) · `./dsa test 06/min_stack`

## Practice
- [ ] `valid_parentheses` · Easy · `./dsa test 06/valid_parentheses`
- [ ] `min_stack` · Medium · `./dsa test 06/min_stack`
- [ ] `eval_rpn` · Medium · `./dsa test 06/eval_rpn`
- [ ] `daily_temperatures` · Medium · `./dsa test 06/daily_temperatures`
- [ ] `car_fleet` · Medium · `./dsa test 06/car_fleet`
- [ ] `largest_rectangle_histogram` · Hard · `./dsa test 06/largest_rectangle_histogram`

## CLRS quick reference (≈25 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Stack and queue basics | §10.1 (3e) / §10.1 (4e), "Stacks and queues" | STACK and ENQUEUE/DEQUEUE pseudocode (≈10 min) | You can implement both on an array and explain overflow and underflow. |
| Before `queue_two_stacks` | §17.1 (3e) / §16.1 (4e), "Aggregate analysis" | The stack-operations example (≈15 min) | You can explain why each element is moved at most twice, so n operations cost O(n). |

Monotonic stacks are not in CLRS. Use the PROBLEM.md hints, or a problem editorial for "next greater element".

## Mastery criteria
- [ ] It can be explained why a monotonic stack achieves O(n) total time.
- [ ] "Next greater element" problems can be recognized and solved without assistance.
