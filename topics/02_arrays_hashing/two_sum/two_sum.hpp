#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>

// Return {i, j} with i < j and nums[i] + nums[j] == target.
// At least one valid pair exists; return any of them.
inline std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // TODO: implement

    std::unordered_map<int, int> map;
    std::vector<int> result;

    // we need to return the indices

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        // check if the complement of n is in the set
        if (map.contains(target - nums[i])) {
            // key (target - nums[i]) exists
            result.push_back(map[target - nums[i]]);
            result.push_back(i);
            break;
        }
        map.insert({nums[i], i});
    }


    return result;
}
