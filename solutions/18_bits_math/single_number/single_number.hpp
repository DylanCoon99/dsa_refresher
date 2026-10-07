#pragma once
#include <vector>

// Approach: XOR all values together.
// Key insight: x ^ x == 0 and XOR is commutative and associative, so the pairs cancel.
// Time: O(n)  Space: O(1)
// Brute force: count occurrences with a hash map (O(n) time, O(n) space) or sort (O(n log n)).
inline int singleNumber(const std::vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}
