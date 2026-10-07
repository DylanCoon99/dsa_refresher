# Last Stone Weight
**Topic:** 11 Heaps and Priority Queues · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Last Stone Weight" (title kept for cross-reference only)

## Problem
You have a collection of stones with positive integer weights. Repeat this round until at most one
stone is left: take the two heaviest stones, with weights `x ≤ y`, and smash them together.
- If `x == y`, both stones vanish.
- Otherwise the stone of weight `x` vanishes and the other becomes a stone of weight `y - x`.

Return the weight of the last remaining stone, or `0` if no stone is left.

In C++ the max-heap you need is simply `std::priority_queue<int>`.

## Examples
- `{2, 7, 4, 1, 8, 1}` → `1` (8 and 7 leave 1; 4 and 2 leave 2; 2 and 1 leave 1; 1 and 1 vanish; one 1 remains)
- `{5}` → `5`
- `{3, 3}` → `0`

## Constraints
- 1 ≤ n ≤ 30 (the tests use at most 30 stones)
- 1 ≤ weight ≤ 1000

## Target
Time: O(n log n) · Space: O(n)

There is no large test: with n ≤ 30 even re-sorting every round is fast, so the tests cannot tell a
heap from re-sorting. The target is stated for practice.

## Hints
<details><summary>Hint 1</summary>Every round needs the two largest elements of a collection that keeps changing. Which structure gives you the maximum quickly while allowing insertions?</details>
<details><summary>Hint 2</summary>After a smash, where does the leftover stone go? What is your stopping condition for the loop, and what do you return when the heap ends up empty?</details>
