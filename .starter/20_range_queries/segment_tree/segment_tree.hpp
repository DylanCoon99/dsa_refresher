#pragma once
#include <vector>

// A segment tree over `values` supporting point assignment and inclusive range sums.
class SegmentTree {
public:
    explicit SegmentTree(const std::vector<long long>& values) {
        // TODO: implement
    }
    // Assign `value` to position i (replace, not add).
    void update(int i, long long value) {
        // TODO: implement
    }
    // Sum of positions l..r inclusive (l <= r).
    long long query(int l, int r) const {
        // TODO: implement
        return 0;
    }

private:
    // Add your fields here.
};
