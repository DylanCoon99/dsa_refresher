#include <eventual_safe_states.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using G = std::vector<std::vector<int>>;

// Brute force: reach[u][v] = v can be reached from u by one or more edges (Floyd-Warshall closure).
// u is unsafe exactly when it can reach some vertex v that can reach itself (a cycle, possibly a self-loop).
std::vector<int> bruteForce(const G& g) {
    int n = static_cast<int>(g.size());
    std::vector<std::vector<char>> reach(n, std::vector<char>(n, 0));
    for (int u = 0; u < n; ++u)
        for (int v : g[u]) reach[u][v] = 1;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
    std::vector<int> safe;
    for (int u = 0; u < n; ++u) {
        bool unsafe = reach[u][u];
        for (int v = 0; v < n && !unsafe; ++v)
            if (reach[u][v] && reach[v][v]) unsafe = true;
        if (!unsafe) safe.push_back(u);
    }
    return safe;
}
}  // namespace

TEST_CASE("examples") {
    // 0 -> 1, 2; 1 -> 2, 3; 2 -> 5; 3 -> 0; 4 -> 5; 5, 6 terminal. The cycle 0 -> 1 -> 3 -> 0 poisons 0, 1, 3.
    G g = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    CHECK(eventualSafeNodes(g) == std::vector<int>{2, 4, 5, 6});
    // Every vertex of a 4-cycle plus a vertex pointing into it is unsafe.
    CHECK(eventualSafeNodes({{1}, {2}, {3}, {0}, {0}}).empty());
}

TEST_CASE("edge cases") {
    SUBCASE("no vertices") { CHECK(eventualSafeNodes({}).empty()); }
    SUBCASE("a single terminal vertex") { CHECK(eventualSafeNodes({{}}) == std::vector<int>{0}); }
    SUBCASE("a self-loop is unsafe") { CHECK(eventualSafeNodes({{0}}).empty()); }
    SUBCASE("a vertex pointing at a self-loop is unsafe too") {
        CHECK(eventualSafeNodes({{1}, {1}, {}}) == std::vector<int>{2});
    }
    SUBCASE("all vertices terminal") { CHECK(eventualSafeNodes({{}, {}, {}}) == std::vector<int>{0, 1, 2}); }
    SUBCASE("a chain ending at a terminal vertex is all safe") {
        CHECK(eventualSafeNodes({{1}, {2}, {3}, {}}) == std::vector<int>{0, 1, 2, 3});
    }
    SUBCASE("a vertex that leads into a cycle is unsafe even if it has a safe exit as well") {
        // 0 -> 1 (terminal) and 0 -> 2; 2 <-> 3 is a cycle.
        CHECK(eventualSafeNodes({{1, 2}, {}, {3}, {2}}) == std::vector<int>{1});
    }
    SUBCASE("a vertex that only reaches the cycle's exit is safe") {
        // 0 -> 1 -> 2 (terminal); 3 -> 0 and 3 -> 3 (self-loop).
        CHECK(eventualSafeNodes({{1}, {2}, {}, {0, 3}}) == std::vector<int>{0, 1, 2});
    }
    SUBCASE("a diamond DAG is all safe") {
        CHECK(eventualSafeNodes({{1, 2}, {3}, {3}, {}}) == std::vector<int>{0, 1, 2, 3});
    }
    SUBCASE("the result is sorted even when the safe vertices are discovered out of order") {
        // 3 -> 2 -> 1 -> 0 (terminal); labels are in reverse order of the edges.
        CHECK(eventualSafeNodes({{}, {0}, {1}, {2}}) == std::vector<int>{0, 1, 2, 3});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        int n = rand_int(1, 8);
        G g(n);
        for (int u = 0; u < n; ++u) {
            int deg = rand_int(0, 2);
            for (int i = 0; i < deg; ++i) {
                int v = rand_int(0, n - 1);
                if (std::find(g[u].begin(), g[u].end(), v) == g[u].end()) g[u].push_back(v);
            }
        }
        INFO("trial " << trial << ", n = " << n);
        CHECK(eventualSafeNodes(g) == bruteForce(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^4 vertices in two parts of 2500 two-vertex layers each. Every vertex of a layer points at both
    // vertices of the next layer, so there are 2^2500 distinct paths from the top. Part A ends at two terminal
    // vertices (everything is safe); in part B the last layer's two vertices point at each other (everything
    // is unsafe). Labels are shuffled. A search that re-explores paths instead of remembering each vertex's
    // verdict never finishes.
    const int layers = 2500, n = 4 * layers;
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng());
    G g(n);
    std::vector<int> expected;
    for (int part = 0; part < 2; ++part) {
        int base = part * 2 * layers;
        for (int l = 0; l < layers; ++l) {
            for (int s = 0; s < 2; ++s) {
                int u = perm[base + 2 * l + s];
                if (l + 1 < layers) {
                    g[u].push_back(perm[base + 2 * (l + 1)]);
                    g[u].push_back(perm[base + 2 * (l + 1) + 1]);
                } else if (part == 1) {
                    g[u].push_back(perm[base + 2 * l + (1 - s)]);
                }
                if (part == 0) expected.push_back(u);
            }
        }
    }
    std::sort(expected.begin(), expected.end());
    std::vector<int> got = eventualSafeNodes(g);
    CHECK(got.size() == expected.size());
    bool same = got == expected;
    CHECK(same);
}
