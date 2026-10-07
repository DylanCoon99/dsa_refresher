# Best Time to Buy and Sell Stock
**Topic:** 04 Sliding Window · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Best Time to Buy and Sell Stock" (title kept for cross-reference only)

## Problem
`prices[i]` is the price of a stock on day `i`. You may buy on one day and sell on a *later*
day (a single transaction), or do nothing. Return the largest profit you can make, or 0 if
every possible transaction loses money or there is nothing to trade.

## Examples
- `prices = {7, 1, 5, 3, 6, 4}` → `5` (buy at 1, sell at 6)
- `prices = {7, 6, 4, 3, 1}` → `0` (prices only fall, so do not trade)
- `prices = {2, 4, 1}` → `2` (buy at 2, sell at 4; the later 1 cannot be sold at a profit)

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ prices[i] ≤ 10⁴

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>If you sell on day j, which earlier day is the best one to have bought on?</details>
<details><summary>Hint 2</summary>Can you carry "the cheapest price so far" along as you scan, so each day costs O(1)?</details>
