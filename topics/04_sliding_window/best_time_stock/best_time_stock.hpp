#pragma once
#include <vector>

// Return the maximum profit from one buy followed by a later sell, or 0 if no profitable trade exists.
inline int maxProfit(const std::vector<int>& prices) {
    // TODO: implement

    if (prices.size() == 1) return 0;

    int highest_profit = 0;
    int i = 0;
    int j = 1;

    while (j < static_cast<int>(prices.size())) {
        int profit = prices[j] - prices[i];
        if (profit <= 0) {
            i = j;
            ++j;
            continue;
        }
        if (profit > highest_profit) {
            highest_profit = profit;
        }
        ++j;
    }

    return highest_profit;
}
