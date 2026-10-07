#pragma once
#include <vector>

// Approach: keep the current values plus a Fenwick tree over them; update adds (val - old).
// Key insight: an assignment is an addition of the difference, and a range sum is two prefix sums.
// Time: O(n) build, O(log n) per call  Space: O(n)
// Brute force: loop over the range per query, O(n); or keep prefix sums and rebuild them per update, O(n).
class NumArray {
public:
    explicit NumArray(const std::vector<int>& nums) : vals_(nums), tree_(nums.size() + 1, 0) {
        for (int i = 1; i < static_cast<int>(tree_.size()); ++i) {
            tree_[i] += vals_[i - 1];
            int parent = i + (i & -i);
            if (parent < static_cast<int>(tree_.size())) tree_[parent] += tree_[i];
        }
    }
    void update(int index, int val) {
        int delta = val - vals_[index];
        vals_[index] = val;
        for (int j = index + 1; j < static_cast<int>(tree_.size()); j += j & -j) tree_[j] += delta;
    }
    int sumRange(int left, int right) const { return prefix(right + 1) - prefix(left); }

private:
    int prefix(int count) const {
        int s = 0;
        for (int j = count; j > 0; j -= j & -j) s += tree_[j];
        return s;
    }
    std::vector<int> vals_;
    std::vector<int> tree_;
};
