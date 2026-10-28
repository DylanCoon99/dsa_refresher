#pragma once
#include <vector>
#include <unordered_map>

// Count contiguous non-empty subarrays of nums whose sum equals k.
// nums may contain negatives and zeros.
inline int subarraySum(const std::vector<int>& nums, int k) {
    // TODO: implement

    int count = 0;
    int running_sum = 0;
    std::unordered_map<int, int> my_map;
    my_map[0] = 1;

    for (int n : nums) {
        running_sum += n;
        count += my_map[running_sum - k];
        ++my_map[running_sum];
    }

    

    return count;
}
