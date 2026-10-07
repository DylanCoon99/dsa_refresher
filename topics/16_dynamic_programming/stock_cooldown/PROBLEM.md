# Best Time to Buy and Sell Stock with Cooldown
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Best Time to Buy and Sell Stock with Cooldown" (title kept for cross-reference only)

## Problem
`prices[i]` is a stock price on day `i`. You may trade as often as you like, but you hold at most one share at a
time (sell before you buy again), and **after selling you cannot buy on the next day** (a one-day cooldown). Return
the maximum total profit; it is 0 if no trade helps.

```cpp
int maxProfit(const std::vector<int>& prices);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.
A "state machine" view helps: name the states you can be in at the end of a day.

## Examples
- `{1, 2, 3, 0, 2}` → `3` (buy 1, sell 2, cooldown, buy 0, sell 2: profit 1 + 2)
- `{1}` → `0`
- `{5, 4, 3, 2, 1}` → `0`

## Constraints
- 1 ≤ prices.size() ≤ 5000; 0 ≤ prices[i] ≤ 1000.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>At the end of each day you are in one of three states: holding a share, just sold (in cooldown), or free (not holding and able to buy). Which states can each one come from the day before?</details>
<details><summary>Hint 2</summary>Write the best profit for each state as a function of the previous day's three values. Which state's value is the answer at the end?</details>
