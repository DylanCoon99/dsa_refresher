#pragma once
#include <vector>

// Approach: fill answer[i] with the product of everything left of i, then sweep right to left
//           multiplying in a running product of everything right of i.
// Key insight: answer[i] = (product of the prefix before i) * (product of the suffix after i); no division needed.
// Time: O(n)  Space: O(1) extra (output excluded)
// Brute force: for each i multiply all other elements, O(n^2).
inline std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    const std::size_t n = nums.size();
    std::vector<int> ans(n, 1);
    for (std::size_t i = 1; i < n; ++i) ans[i] = ans[i - 1] * nums[i - 1];
    int right = 1;
    for (std::size_t i = n; i-- > 0;) {
        ans[i] *= right;
        right *= nums[i];
    }
    return ans;
}
