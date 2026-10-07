#pragma once
#include <algorithm>
#include <climits>
#include <vector>

// Approach: three states at the end of each day: hold (own a share), sold (just sold, in cooldown) and rest
//           (free, not holding). hold' = max(hold, rest - p); sold' = hold + p; rest' = max(rest, sold).
// Key insight: the cooldown only constrains where "free" can come from: buying needs yesterday to be free.
// Time: O(n)  Space: O(1)
// Brute force: recurse over (day, holding) choosing buy / sell / skip, jumping two days after a sell: exponential.
inline int maxProfit(const std::vector<int>& prices) {
    int hold = INT_MIN / 2, sold = 0, rest = 0;
    for (int p : prices) {
        int newHold = std::max(hold, rest - p);
        int newSold = hold + p;
        int newRest = std::max(rest, sold);
        hold = newHold;
        sold = newSold;
        rest = newRest;
    }
    return std::max(sold, rest);
}
