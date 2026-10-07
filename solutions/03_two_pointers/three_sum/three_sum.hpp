#pragma once
#include <algorithm>
#include <vector>

// Approach: sort; fix the smallest element i, then run opposite-direction pointers on the rest looking for sum -nums[i].
//           Skip equal values for i, and after each hit skip equal values on both pointers.
// Key insight: sorting makes Two Sum II an O(n) sweep, and skipping equal neighbours removes duplicate triplets without a set.
// Time: O(n^2)  Space: O(1) extra beyond the output
// Brute force: try all triples and put sorted triplets in a set: O(n^3) time.
inline std::vector<std::vector<int>> threeSum(std::vector<int> nums) {
    std::vector<std::vector<int>> out;
    std::sort(nums.begin(), nums.end());
    const int n = static_cast<int>(nums.size());
    for (int i = 0; i + 2 < n; ++i) {
        if (nums[i] > 0) break;
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            const int sum = nums[i] + nums[lo] + nums[hi];
            if (sum < 0) {
                ++lo;
            } else if (sum > 0) {
                --hi;
            } else {
                out.push_back({nums[i], nums[lo], nums[hi]});
                ++lo;
                --hi;
                while (lo < hi && nums[lo] == nums[lo - 1]) ++lo;
                while (lo < hi && nums[hi] == nums[hi + 1]) --hi;
            }
        }
    }
    return out;
}
