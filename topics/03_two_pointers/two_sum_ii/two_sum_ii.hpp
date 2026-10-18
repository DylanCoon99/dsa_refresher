#pragma once
#include <vector>

// numbers is sorted ascending. Return the 1-based positions {i, j}, i < j,
// with numbers[i-1] + numbers[j-1] == target. Exactly one solution exists. Use O(1) extra space.
inline std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
    // TODO: implement

    int i = 0;
    int j = numbers.size() - 1;

    while (i < j) {
        // calculate the sum
        int two_sum = numbers[i] + numbers[j];
        if (two_sum == target) {
            break;
        }
        // update j and i accordingly
        if (two_sum > target) {
            --j;
        } else {
            ++i;
        }
    }

    return {i + 1, j + 1};
}
