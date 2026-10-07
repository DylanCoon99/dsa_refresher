#pragma once
#include <utility>
#include <vector>

// Approach: parent array with path compression in an iterative find; unite links the smaller tree under the larger (union by size) and tracks the component count.
// Key insight: compression flattens every path walked and union by size keeps trees shallow, so together a find costs inverse-Ackermann amortized.
// Time: O(alpha(n)) amortized per operation  Space: O(n)
// Brute force: no heuristics (parent[root(a)] = root(b)); a chain of n unions makes each find O(n), so n finds cost O(n^2).
class UnionFind {
public:
    explicit UnionFind(int n) : parent_(n), size_(n, 1), count_(n) {
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }
    int find(int x) {
        int root = x;
        while (parent_[root] != root) root = parent_[root];
        while (parent_[x] != root) {
            int next = parent_[x];
            parent_[x] = root;
            x = next;
        }
        return root;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        --count_;
        return true;
    }
    bool connected(int a, int b) { return find(a) == find(b); }
    int componentCount() const { return count_; }
    int componentSize(int x) { return size_[find(x)]; }

private:
    std::vector<int> parent_;
    std::vector<int> size_;
    int count_ = 0;
};
