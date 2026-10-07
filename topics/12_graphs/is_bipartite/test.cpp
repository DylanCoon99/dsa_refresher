#include <is_bipartite.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

namespace {
using G = std::vector<std::vector<int>>;

// Brute force: try every assignment of the vertices to two groups.
bool brute(const G& g) {
    int n = static_cast<int>(g.size());
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int v = 0; v < n && ok; ++v)
            for (int w : g[v])
                if (((mask >> v) & 1) == ((mask >> w) & 1)) {
                    ok = false;
                    break;
                }
        if (ok) return true;
    }
    return false;
}

G cycle(int n) {
    G g(n);
    for (int i = 0; i < n; ++i) {
        g[i].push_back((i + 1) % n);
        g[(i + 1) % n].push_back(i);
    }
    return g;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(isBipartite({{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}}) == false);
    CHECK(isBipartite({{1, 3}, {0, 2}, {1, 3}, {0, 2}}) == true);
    CHECK(isBipartite({{1}, {0}}) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("single vertex") { CHECK(isBipartite({{}}) == true); }
    SUBCASE("isolated vertices only") { CHECK(isBipartite({{}, {}, {}}) == true); }
    SUBCASE("odd cycle") {
        CHECK(isBipartite(cycle(3)) == false);
        CHECK(isBipartite(cycle(5)) == false);
        CHECK(isBipartite(cycle(9)) == false);
    }
    SUBCASE("even cycle") {
        CHECK(isBipartite(cycle(4)) == true);
        CHECK(isBipartite(cycle(6)) == true);
        CHECK(isBipartite(cycle(10)) == true);
    }
    SUBCASE("disconnected, one component is not bipartite") {
        // Component {0,1} is an edge; component {2,3,4} is a triangle.
        CHECK(isBipartite({{1}, {0}, {3, 4}, {2, 4}, {2, 3}}) == false);
        // Same, with the bad component listed first.
        CHECK(isBipartite({{1, 2}, {0, 2}, {0, 1}, {4}, {3}}) == false);
    }
    SUBCASE("disconnected, all components bipartite") { CHECK(isBipartite({{1}, {0}, {3}, {2}, {}}) == true); }
    SUBCASE("odd cycle behind isolated vertices") {
        CHECK(isBipartite({{}, {}, {3, 4}, {2, 4}, {2, 3}}) == false);
    }
    SUBCASE("a path and a star are bipartite") {
        CHECK(isBipartite({{1}, {0, 2}, {1, 3}, {2}}) == true);
        CHECK(isBipartite({{1, 2, 3, 4}, {0}, {0}, {0}, {0}}) == true);
    }
    SUBCASE("complete bipartite K2,3 vs K4") {
        CHECK(isBipartite({{2, 3, 4}, {2, 3, 4}, {0, 1}, {0, 1}, {0, 1}}) == true);
        CHECK(isBipartite({{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}}) == false);
    }
}

TEST_CASE("randomized vs 2^n brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 9), m = rand_int(0, 12);
        std::set<std::pair<int, int>> edges;
        for (int i = 0; i < m; ++i) {
            int u = rand_int(0, n - 1), v = rand_int(0, n - 1);
            if (u == v) continue;
            edges.insert({std::min(u, v), std::max(u, v)});
        }
        G g(n);
        for (const auto& [u, v] : edges) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
        CHECK(isBipartite(g) == brute(g));
    }
}
