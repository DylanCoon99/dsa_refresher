#pragma once
#include <vector>

// Approach: store prefix[i] = sum of the first i elements; the answer is prefix[right+1] - prefix[left].
// Key insight: a range sum is the difference of two prefix sums, so queries need no loop.
// Time: O(n) build, O(1) query  Space: O(n)
// Brute force: add up nums[left..right] for every query, O(n) per query.
class NumArray {
public:
    explicit NumArray(const std::vector<int>& nums) : prefix_(nums.size() + 1, 0) {
        for (std::size_t i = 0; i < nums.size(); ++i) prefix_[i + 1] = prefix_[i] + nums[i];
    }

    int sumRange(int left, int right) const { return prefix_[right + 1] - prefix_[left]; }

private:
    std::vector<int> prefix_;
};
