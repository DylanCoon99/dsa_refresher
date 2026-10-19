#pragma once
#include <vector>
#include <algorithm>

// Return all distinct triplets of values (from three different positions) that sum to 0.
// Triplets and the result may be in any order; each distinct triplet appears once.
inline std::vector<std::vector<int>> threeSum(std::vector<int> nums) {
    // TODO: implement
    std::vector<std::vector<int>> result;

    // sort the vector first
    std::sort(nums.begin(), nums.end());

    int i;
    int j;
    int n;
    int sum;
    int k_prev;
    
    for (int k = 0; k < nums.size(); ++k) {
        // for each n, use a 2 pointer approach; check if the numbers add to 0
        if (k > 0 && k_prev == nums[k]) {
            continue;
        }
        k_prev = nums[k];
        n = nums[k];
        i = k + 1;
        j = nums.size() - 1;
        while (i < j) {

            sum = n + nums[i] + nums[j];
            if (sum == 0) {
                result.push_back({n, nums[i], nums[j]});
                int temp_i = nums[i];
                int temp_j = nums[j];

                while (temp_i == nums[i] && i < j) {
                    ++i;
                }

                while (temp_j == nums[j] && i < j) {
                    --j;
                }
                
            }
            if (sum > 0) {
                --j;
            }
            if (sum < 0) {
                ++i;
            }
        }

    }

    return result;
}
