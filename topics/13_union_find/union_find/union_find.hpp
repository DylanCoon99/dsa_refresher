#pragma once
#include <vector>

// Disjoint sets over 0..n-1 with path compression and union by rank or size.
// unite returns false if a and b were already connected (including a == b).
class UnionFind {
public:
    explicit UnionFind(int n) {
        // TODO: implement
    }
    int find(int x) {
        // TODO: implement
        return -1;
    }
    bool unite(int a, int b) {
        // TODO: implement
        return false;
    }
    bool connected(int a, int b) {
        // TODO: implement
        return false;
    }
    int componentCount() const {
        // TODO: implement
        return 0;
    }
    int componentSize(int x) {
        // TODO: implement
        return 0;
    }

private:
    std::vector<int> parent_;
    std::vector<int> size_;
    int count_ = 0;
};
