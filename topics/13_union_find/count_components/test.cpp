#include <count_components.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Edges = std::vector<std::vector<int>>;

// Brute force: flood fill from every unvisited node over a full adjacency matrix.
int brute(int n, const Edges& edges) {
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    for (const auto& e : edges) adj[e[0]][e[1]] = adj[e[1]][e[0]] = true;
    std::vector<bool> seen(n, false);
    int comps = 0;
    for (int s = 0; s < n; ++s) {
        if (seen[s]) continue;
        ++comps;
        std::vector<int> stack{s};
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v = 0; v < n; ++v)
                if (adj[u][v] && !seen[v]) {
                    seen[v] = true;
                    stack.push_back(v);
                }
        }
    }
    return comps;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(countComponents(5, {{0, 1}, {1, 2}, {3, 4}}) == 2);
    CHECK(countComponents(4, {}) == 4);
    CHECK(countComponents(3, {{0, 1}, {1, 0}, {0, 1}}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("no edges returns n") {
        CHECK(countComponents(1, {}) == 1);
        CHECK(countComponents(7, {}) == 7);
    }
    SUBCASE("one component") {
        CHECK(countComponents(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}) == 1);
        CHECK(countComponents(4, {{0, 1}, {0, 2}, {0, 3}}) == 1);
        CHECK(countComponents(3, {{0, 1}, {1, 2}, {2, 0}}) == 1);
    }
    SUBCASE("duplicate edges") {
        CHECK(countComponents(4, {{0, 1}, {0, 1}, {1, 0}, {2, 3}, {2, 3}}) == 2);
        CHECK(countComponents(2, {{1, 0}, {0, 1}}) == 1);
    }
    SUBCASE("components joined out of order") {
        CHECK(countComponents(6, {{4, 5}, {0, 1}, {2, 3}, {1, 2}, {3, 4}}) == 1);
    }
    SUBCASE("isolated nodes next to a component") { CHECK(countComponents(6, {{1, 2}, {2, 3}}) == 4); }
}

TEST_CASE("randomized vs flood fill") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 12);
        int m = rand_int(0, 14);
        Edges edges;
        if (n >= 2)
            for (int i = 0; i < m; ++i) {
                int u = rand_int(0, n - 1), v = rand_int(0, n - 2);
                if (v >= u) ++v;  // v != u
                edges.push_back({u, v});
            }
        CHECK(countComponents(n, edges) == brute(n, edges));
    }
}
