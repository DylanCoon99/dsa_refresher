#pragma once
#include <vector>

// Approach: pointers at both ends; if the sum is too large move the right one in, if too small move the left one in.
// Key insight: sortedness means a too-large sum can only be fixed by moving the right pointer, so the discarded element can never be in a valid pair.
// Time: O(n)  Space: O(1)
// Brute force: try every pair, O(n^2); or a hash map, O(n) space; or binary search per element, O(n log n).
inline std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
    int i = 0, j = static_cast<int>(numbers.size()) - 1;
    while (i < j) {
        const long long sum = static_cast<long long>(numbers[i]) + numbers[j];
        if (sum == target) return {i + 1, j + 1};
        if (sum < target) ++i; else --j;
    }
    return {};
}
