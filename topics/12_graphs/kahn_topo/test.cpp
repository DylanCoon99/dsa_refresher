#include <kahn_topo.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

namespace {
using Edges = std::vector<std::pair<int, int>>;

// True when `order` is a permutation of 0..n-1 in which every edge goes forward.
bool validOrder(int n, const Edges& edges, const std::vector<int>& order) {
    if (static_cast<int>(order.size()) != n) return false;
    std::vector<int> pos(n, -1);
    for (int i = 0; i < n; ++i) {
        if (order[i] < 0 || order[i] >= n || pos[order[i]] != -1) return false;
        pos[order[i]] = i;
    }
    for (const auto& [u, v] : edges)
        if (pos[u] >= pos[v]) return false;
    return true;
}

void checkDag(int n, const Edges& edges) {
    auto order = topoSortKahn(n, edges);
    CHECK(validOrder(n, edges, order));
}

void checkCycle(int n, const Edges& edges) { CHECK(topoSortKahn(n, edges).empty()); }

// Brute force: a valid order exists iff some permutation puts every edge forward.
bool hasOrder(int n, const Edges& edges) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    do {
        if (validOrder(n, edges, p)) return true;
    } while (std::next_permutation(p.begin(), p.end()));
    return false;
}
}  // namespace

TEST_CASE("examples") {
    checkDag(4, {{0, 1}, {0, 2}, {1, 3}, {2, 3}});
    checkDag(3, {{2, 1}, {1, 0}});
    CHECK(topoSortKahn(3, {{2, 1}, {1, 0}}) == std::vector<int>{2, 1, 0});  // the only valid order
    checkCycle(3, {{0, 1}, {1, 2}, {2, 0}});
}

TEST_CASE("edge cases") {
    SUBCASE("no edges: every vertex appears") { checkDag(5, {}); }
    SUBCASE("single vertex") { CHECK(topoSortKahn(1, {}) == std::vector<int>{0}); }
    SUBCASE("self-loop is a cycle") {
        checkCycle(1, {{0, 0}});
        checkCycle(3, {{0, 1}, {1, 1}});
    }
    SUBCASE("2-cycle") { checkCycle(2, {{0, 1}, {1, 0}}); }
    SUBCASE("cycle hidden behind a valid prefix") { checkCycle(5, {{0, 1}, {1, 2}, {2, 3}, {3, 1}, {3, 4}}); }
    SUBCASE("cycle in one component, other component is a DAG") { checkCycle(6, {{0, 1}, {2, 3}, {3, 4}, {4, 2}}); }
    SUBCASE("multiple components") { checkDag(7, {{0, 1}, {1, 2}, {3, 4}, {5, 6}, {4, 6}}); }
    SUBCASE("diamond and repeated edges") { checkDag(4, {{0, 1}, {0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 3}}); }
    SUBCASE("edges listed against the label order") { checkDag(4, {{3, 2}, {2, 1}, {1, 0}}); }
}

TEST_CASE("randomized vs permutation brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 7), m = rand_int(0, 9);
        Edges edges;
        for (int i = 0; i < m; ++i) edges.push_back({rand_int(0, n - 1), rand_int(0, n - 1)});
        auto got = topoSortKahn(n, edges);
        if (hasOrder(n, edges)) {
            CHECK(validOrder(n, edges, got));
        } else {
            CHECK(got.empty());
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // A chain over 10^5 vertices with shuffled labels: perm[0] -> perm[1] -> ... -> perm[n-1].
    // The only valid order is perm itself.
    const int n = 100'000;
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng());
    Edges edges;
    for (int i = 0; i + 1 < n; ++i) edges.push_back({perm[i], perm[i + 1]});
    std::shuffle(edges.begin(), edges.end(), rng());
    auto got = topoSortKahn(n, edges);
    bool same = got == perm;
    CHECK(same);
}
