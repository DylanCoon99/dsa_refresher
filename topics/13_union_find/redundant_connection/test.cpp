#include <redundant_connection.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Edges = std::vector<std::vector<int>>;

// True if the edges, with edge `skip` removed, connect all n nodes (n - 1 edges that connect n nodes form a tree).
bool leavesTree(int n, const Edges& edges, std::size_t skip) {
    std::vector<std::vector<bool>> adj(n + 1, std::vector<bool>(n + 1, false));
    for (std::size_t i = 0; i < edges.size(); ++i)
        if (i != skip) adj[edges[i][0]][edges[i][1]] = adj[edges[i][1]][edges[i][0]] = true;
    std::vector<bool> seen(n + 1, false);
    std::vector<int> stack{1};
    seen[1] = true;
    int reached = 0;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        ++reached;
        for (int v = 1; v <= n; ++v)
            if (adj[u][v] && !seen[v]) {
                seen[v] = true;
                stack.push_back(v);
            }
    }
    return reached == n;
}

// Brute force: the last edge whose removal leaves a connected graph on n - 1 edges.
std::vector<int> brute(const Edges& edges) {
    int n = static_cast<int>(edges.size());
    for (std::size_t i = edges.size(); i-- > 0;)
        if (leavesTree(n, edges, i)) return edges[i];
    return {};
}
}  // namespace

TEST_CASE("examples") {
    CHECK(findRedundantConnection({{1, 2}, {1, 3}, {2, 3}}) == std::vector<int>{2, 3});
    CHECK(findRedundantConnection({{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}) == std::vector<int>{1, 4});
    CHECK(findRedundantConnection({{1, 2}, {1, 3}, {3, 2}, {4, 1}}) == std::vector<int>{3, 2});
}

TEST_CASE("edge cases") {
    SUBCASE("cycle edge is the last edge") {
        CHECK(findRedundantConnection({{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}}) == std::vector<int>{5, 1});
        CHECK(findRedundantConnection({{1, 2}, {1, 3}, {1, 4}, {3, 4}}) == std::vector<int>{3, 4});
    }
    SUBCASE("cycle edge is in the middle: the later cycle edge wins") {
        CHECK(findRedundantConnection({{1, 2}, {2, 3}, {1, 3}, {3, 4}, {4, 5}}) == std::vector<int>{1, 3});
        CHECK(findRedundantConnection({{2, 3}, {1, 2}, {3, 1}, {4, 1}}) == std::vector<int>{3, 1});
    }
    SUBCASE("3-node triangle, every rotation") {
        CHECK(findRedundantConnection({{1, 2}, {2, 3}, {3, 1}}) == std::vector<int>{3, 1});
        CHECK(findRedundantConnection({{3, 1}, {1, 2}, {2, 3}}) == std::vector<int>{2, 3});
        CHECK(findRedundantConnection({{2, 3}, {3, 1}, {1, 2}}) == std::vector<int>{1, 2});
    }
    SUBCASE("orientation of the returned edge is kept") {
        CHECK(findRedundantConnection({{1, 2}, {2, 3}, {3, 1}}) == std::vector<int>{3, 1});
        CHECK(findRedundantConnection({{2, 1}, {3, 2}, {1, 3}}) == std::vector<int>{1, 3});
    }
    SUBCASE("a pendant edge after the cycle is not returned") {
        CHECK(findRedundantConnection({{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}}) == std::vector<int>{3, 1});
    }
}

TEST_CASE("randomized vs remove-and-check") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(3, 10);
        std::vector<int> label(n);
        std::iota(label.begin(), label.end(), 1);
        std::shuffle(label.begin(), label.end(), rng());
        Edges edges;
        std::vector<std::vector<bool>> has(n + 1, std::vector<bool>(n + 1, false));
        auto add = [&](int a, int b) {
            edges.push_back({a, b});
            has[a][b] = has[b][a] = true;
        };
        for (int i = 1; i < n; ++i) {  // random tree: node i attaches to an earlier node
            int a = label[rand_int(0, i - 1)], b = label[i];
            if (rand_int(0, 1)) std::swap(a, b);
            add(a, b);
        }
        for (;;) {  // one extra edge between two nodes that are not yet adjacent
            int a = rand_int(1, n), b = rand_int(1, n);
            if (a != b && !has[a][b]) {
                edges.push_back({a, b});
                break;
            }
        }
        std::shuffle(edges.begin(), edges.end(), rng());
        CHECK(findRedundantConnection(edges) == brute(edges));
    }
}
