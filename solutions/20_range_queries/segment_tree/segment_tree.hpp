#pragma once
#include <vector>

// Approach: bottom-up array tree of size 2n: leaves at [n, 2n), node i = tree[2i] + tree[2i+1].
//           Updates rewrite the leaf and walk to the root; queries peel off whole blocks from both ends.
// Key insight: every node's sum is derived from its two children, so a point change touches one root-to-leaf path.
// Time: O(n) build, O(log n) per call  Space: O(n)
// Brute force: scan the array on every query, O(n) per query.
class SegmentTree {
public:
    explicit SegmentTree(const std::vector<long long>& values)
        : n_(static_cast<int>(values.size())), tree_(2 * values.size(), 0) {
        for (int i = 0; i < n_; ++i) tree_[n_ + i] = values[i];
        for (int i = n_ - 1; i >= 1; --i) tree_[i] = tree_[2 * i] + tree_[2 * i + 1];
    }
    void update(int i, long long value) {
        int p = i + n_;
        tree_[p] = value;
        for (p /= 2; p >= 1; p /= 2) tree_[p] = tree_[2 * p] + tree_[2 * p + 1];
    }
    long long query(int l, int r) const {
        long long s = 0;
        for (int lo = l + n_, hi = r + n_ + 1; lo < hi; lo /= 2, hi /= 2) {
            if (lo & 1) s += tree_[lo++];
            if (hi & 1) s += tree_[--hi];
        }
        return s;
    }

private:
    int n_;
    std::vector<long long> tree_;
};
