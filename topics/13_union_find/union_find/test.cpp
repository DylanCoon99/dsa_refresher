#include <union_find.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <queue>
#include <vector>

namespace {
// Brute force: keep the edges that were united and answer by BFS over them.
struct BruteGraph {
    int n;
    std::vector<std::vector<bool>> adj;
    explicit BruteGraph(int n_) : n(n_), adj(n_, std::vector<bool>(n_, false)) {}

    // Component label of every vertex, by BFS.
    std::vector<int> labels() const {
        std::vector<int> label(n, -1);
        int next = 0;
        for (int s = 0; s < n; ++s) {
            if (label[s] != -1) continue;
            std::queue<int> q;
            q.push(s);
            label[s] = next;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v)
                    if (adj[u][v] && label[v] == -1) {
                        label[v] = next;
                        q.push(v);
                    }
            }
            ++next;
        }
        return label;
    }
};
}  // namespace

TEST_CASE("examples") {
    UnionFind uf(5);
    CHECK(uf.unite(0, 1) == true);
    CHECK(uf.unite(1, 2) == true);
    CHECK(uf.connected(0, 2) == true);
    CHECK(uf.componentCount() == 3);
    CHECK(uf.unite(2, 0) == false);
    CHECK(uf.componentSize(0) == 3);
    CHECK(uf.componentSize(3) == 1);
    CHECK(uf.unite(4, 4) == false);
}

TEST_CASE("fresh structure") {
    UnionFind uf(4);
    CHECK(uf.componentCount() == 4);
    for (int i = 0; i < 4; ++i) {
        CHECK(uf.find(i) == i);
        CHECK(uf.componentSize(i) == 1);
        CHECK(uf.connected(i, i) == true);
    }
    CHECK(uf.connected(0, 3) == false);
}

TEST_CASE("single element") {
    UnionFind uf(1);
    CHECK(uf.componentCount() == 1);
    CHECK(uf.find(0) == 0);
    CHECK(uf.unite(0, 0) == false);
    CHECK(uf.componentSize(0) == 1);
}

TEST_CASE("self-union changes nothing") {
    UnionFind uf(3);
    CHECK(uf.unite(1, 1) == false);
    CHECK(uf.componentCount() == 3);
    CHECK(uf.componentSize(1) == 1);
    CHECK(uf.connected(0, 1) == false);
}

TEST_CASE("repeated unions") {
    UnionFind uf(4);
    CHECK(uf.unite(0, 1) == true);
    CHECK(uf.unite(0, 1) == false);
    CHECK(uf.unite(1, 0) == false);
    CHECK(uf.componentCount() == 3);
    CHECK(uf.unite(2, 3) == true);
    CHECK(uf.unite(1, 2) == true);
    CHECK(uf.unite(0, 3) == false);
    CHECK(uf.componentCount() == 1);
}

TEST_CASE("sizes after merges") {
    UnionFind uf(10);
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(3, 4);
    CHECK(uf.componentSize(1) == 2);
    CHECK(uf.componentSize(4) == 3);
    CHECK(uf.componentSize(9) == 1);
    CHECK(uf.unite(4, 0) == true);  // sizes 3 and 2
    for (int x : {0, 1, 2, 3, 4}) CHECK(uf.componentSize(x) == 5);
    CHECK(uf.componentSize(5) == 1);
    CHECK(uf.componentCount() == 6);
    uf.unite(5, 6);
    uf.unite(7, 8);
    uf.unite(6, 7);
    CHECK(uf.unite(9, 8) == true);  // a singleton joins a set of 4
    CHECK(uf.componentSize(5) == 5);
    CHECK(uf.componentSize(9) == 5);
    CHECK(uf.unite(0, 9) == true);  // 5 + 5
    CHECK(uf.componentSize(6) == 10);
    CHECK(uf.componentCount() == 1);
}

TEST_CASE("find is a consistent representative") {
    UnionFind uf(8);
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(1, 3);
    int r = uf.find(0);
    for (int x : {0, 1, 2, 3}) CHECK(uf.find(x) == r);
    CHECK(uf.find(r) == r);
    CHECK(uf.find(4) == 4);
    CHECK(uf.find(4) != r);
}

TEST_CASE("randomized vs BFS connectivity") {
    // 1000 rounds x 100 operations = 10^5 operations on n = 50.
    const int n = 50;
    for (int round = 0; round < 1000; ++round) {
        UnionFind uf(n);
        BruteGraph g(n);
        std::vector<int> label = g.labels();
        for (int op = 0; op < 100; ++op) {
            int a = rand_int(0, n - 1), b = rand_int(0, n - 1);
            int kind = rand_int(0, 5);
            if (kind <= 1) {
                bool expect = label[a] != label[b];
                bool got = uf.unite(a, b);
                REQUIRE(got == expect);
                g.adj[a][b] = g.adj[b][a] = true;
                label = g.labels();
            } else if (kind <= 3) {
                REQUIRE(uf.connected(a, b) == (label[a] == label[b]));
            } else if (kind == 4) {
                int size = 0;
                for (int v = 0; v < n; ++v) size += label[v] == label[a];
                REQUIRE(uf.componentSize(a) == size);
            } else {
                int comps = 0;
                for (int v = 0; v < n; ++v) comps = std::max(comps, label[v] + 1);
                REQUIRE(uf.componentCount() == comps);
            }
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Two chains of 10^6 elements, one built with unite(i, i+1) and one with unite(i+1, i),
    // so that a solution with no heuristics linking in either fixed direction gets a path of length 10^6.
    // Then 10^6 finds on element 0 in each. Expected: one component of size n, the same root every time.
    const int n = 1'000'000;
    for (int direction = 0; direction < 2; ++direction) {
        UnionFind uf(n);
        int merged = 0;
        for (int i = 0; i + 1 < n; ++i) merged += direction == 0 ? uf.unite(i, i + 1) : uf.unite(i + 1, i);
        CHECK(merged == n - 1);
        CHECK(uf.componentCount() == 1);
        int root = uf.find(0);
        int mismatches = 0;
        for (int i = 0; i < n; ++i) mismatches += uf.find(0) != root;
        CHECK(mismatches == 0);
        CHECK(uf.find(n - 1) == root);
        CHECK(uf.componentSize(0) == n);
    }
}
