#include <kruskal.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

namespace {
using Edge = std::tuple<int, int, int>;

// Brute force: Prim's algorithm in O(V^2) on an adjacency matrix (parallel edges keep the minimum).
long long brutePrim(int n, const std::vector<Edge>& edges) {
    const long long NONE = 4'000'000'000'000LL;
    std::vector<std::vector<long long>> w(n, std::vector<long long>(n, NONE));
    for (auto [u, v, c] : edges) {
        if (u == v) continue;
        w[u][v] = std::min<long long>(w[u][v], c);
        w[v][u] = std::min<long long>(w[v][u], c);
    }
    std::vector<bool> in(n, false);
    std::vector<long long> best(n, NONE);
    best[0] = 0;
    long long total = 0;
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!in[v] && (u == -1 || best[v] < best[u])) u = v;
        if (best[u] == NONE) return -1;
        in[u] = true;
        total += best[u];
        for (int v = 0; v < n; ++v)
            if (!in[v] && w[u][v] < best[v]) best[v] = w[u][v];
    }
    return total;
}

// A tiny xorshift generator (fixed seed) for the large test: cheaper than rand_int in a Debug build.
struct FastRng {
    unsigned long long s = 88172645463325252ULL;
    int next(int lo, int hi) {
        s ^= s << 13;
        s ^= s >> 7;
        s ^= s << 17;
        return lo + static_cast<int>((s >> 11) % static_cast<unsigned long long>(hi - lo + 1));
    }
};
}  // namespace

TEST_CASE("examples") {
    CHECK(kruskalMstWeight(4, {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}, {2, 3, 4}}) == 7);
    CHECK(kruskalMstWeight(4, {{0, 1, 5}, {2, 3, 6}}) == -1);
    CHECK(kruskalMstWeight(3, {{0, 1, -2}, {1, 2, -3}, {0, 2, 1}}) == -5);
}

TEST_CASE("disconnected graphs return -1") {
    CHECK(kruskalMstWeight(2, {}) == -1);
    CHECK(kruskalMstWeight(3, {{0, 1, 1}}) == -1);
    CHECK(kruskalMstWeight(5, {{0, 1, 1}, {1, 2, 1}, {0, 2, 1}, {3, 3, 1}}) == -1);
    // Enough edges but they all sit inside one component.
    CHECK(kruskalMstWeight(4, {{0, 1, 1}, {1, 2, 1}, {0, 2, 1}, {0, 2, 7}}) == -1);
}

TEST_CASE("single vertex") {
    CHECK(kruskalMstWeight(1, {}) == 0);
    CHECK(kruskalMstWeight(1, {{0, 0, 5}}) == 0);
    CHECK(kruskalMstWeight(1, {{0, 0, -5}}) == 0);
}

TEST_CASE("negative weights") {
    CHECK(kruskalMstWeight(2, {{0, 1, -7}}) == -7);
    // The total of a connected graph may be exactly -1; that is a weight, not "disconnected".
    CHECK(kruskalMstWeight(3, {{0, 1, -3}, {1, 2, 2}, {0, 2, 5}}) == -1);
    CHECK(kruskalMstWeight(4, {{0, 1, -10}, {1, 2, -10}, {2, 3, -10}, {0, 3, -1}, {0, 2, 4}}) == -30);
}

TEST_CASE("parallel edges and self-loops") {
    CHECK(kruskalMstWeight(2, {{0, 1, 9}, {1, 0, 4}, {0, 1, 6}}) == 4);
    CHECK(kruskalMstWeight(3, {{0, 0, -100}, {0, 1, 2}, {1, 1, -100}, {1, 2, 3}, {2, 2, -100}}) == 5);
}

TEST_CASE("weights near the int limits") {
    std::vector<Edge> edges;
    for (int i = 0; i + 1 < 5; ++i) edges.push_back({i, i + 1, 1'000'000'000});
    CHECK(kruskalMstWeight(5, edges) == 4'000'000'000LL);
    std::vector<Edge> neg;
    for (int i = 0; i + 1 < 5; ++i) neg.push_back({i, i + 1, -1'000'000'000});
    CHECK(kruskalMstWeight(5, neg) == -4'000'000'000LL);
}

TEST_CASE("randomized vs Prim") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 10);
        int m = rand_int(0, 25);
        std::vector<Edge> edges;
        for (int i = 0; i < m; ++i) edges.push_back({rand_int(0, n - 1), rand_int(0, n - 1), rand_int(-10, 10)});
        REQUIRE(kruskalMstWeight(n, edges) == brutePrim(n, edges));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 vertices, 3*10^5 edges. A random spanning tree (vertex i attaches to a random earlier vertex,
    // then labels are shuffled) has weights in [1, 1000]. Every one of the 2*10^5 extra edges weighs more
    // than 1000, so each is the heaviest edge on the cycle it closes and is never in the MST.
    // Expected total = the sum of the tree weights.
    const int n = 100'000, extra = 200'001;
    FastRng fr;
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    for (int i = n - 1; i > 0; --i) std::swap(p[i], p[fr.next(0, i)]);
    std::vector<Edge> edges;
    long long expected = 0;
    for (int i = 1; i < n; ++i) {
        int w = fr.next(1, 1000);
        expected += w;
        edges.push_back({p[fr.next(0, i - 1)], p[i], w});
    }
    for (int e = 0; e < extra; ++e) edges.push_back({fr.next(0, n - 1), fr.next(0, n - 1), fr.next(1001, 1'000'000'000)});
    for (size_t i = edges.size() - 1; i > 0; --i) std::swap(edges[i], edges[fr.next(0, static_cast<int>(i))]);
    CHECK(edges.size() == static_cast<size_t>(n - 1 + extra));
    CHECK(kruskalMstWeight(n, edges) == expected);
}
