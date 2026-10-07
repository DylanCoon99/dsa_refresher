#pragma once
#include <vector>

// A Fenwick tree (binary indexed tree) over positions 0..n-1, all initially 0.
// The public API is 0-indexed; convert to 1-indexed inside.
class FenwickTree {
public:
    explicit FenwickTree(int n) {
        // TODO: implement
    }
    // Add `delta` (possibly negative) to position i.
    void add(int i, long long delta) {
        // TODO: implement
    }
    // Sum of positions 0..i inclusive. prefixSum(-1) == 0.
    long long prefixSum(int i) const {
        // TODO: implement
        return 0;
    }
    // Sum of positions l..r inclusive (l <= r).
    long long rangeSum(int l, int r) const {
        // TODO: implement
        return 0;
    }

private:
    // Add your fields here.
};
