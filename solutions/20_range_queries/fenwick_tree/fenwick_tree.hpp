#pragma once
#include <vector>

// Approach: cell j (1-indexed) holds the sum of the (j & -j) positions ending at j;
//           prefix queries walk j -= j & -j, updates walk j += j & -j.
// Key insight: the lowest set bit of an index is the size of the block it owns, so both walks take O(log n) steps.
// Time: O(log n) per call  Space: O(n)
// Brute force: a plain array with O(n) range sums (or O(n) prefix rebuild on each add).
class FenwickTree {
public:
    explicit FenwickTree(int n) : tree_(n + 1, 0) {}
    void add(int i, long long delta) {
        for (int j = i + 1; j < static_cast<int>(tree_.size()); j += j & -j) tree_[j] += delta;
    }
    long long prefixSum(int i) const {
        long long s = 0;
        for (int j = i + 1; j > 0; j -= j & -j) s += tree_[j];
        return s;
    }
    long long rangeSum(int l, int r) const { return prefixSum(r) - prefixSum(l - 1); }

private:
    std::vector<long long> tree_;
};
