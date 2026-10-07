#include <dijkstra.hpp>

#include <doctest.h>
#include <graph.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

namespace {
using Edge = std::tuple<int, int, int>;  // from, to, weight

WeightedGraph build(int n, const std::vector<Edge>& edges) {
    WeightedGraph g(n);
    for (auto [u, v, w] : edges) g[u].emplace_back(v, w);
    return g;
}

// Brute force: Bellman-Ford over the edge list, n - 1 rounds.
std::vector<long long> bellmanFord(int n, const std::vector<Edge>& edges, int src) {
    std::vector<long long> dist(n, kUnreachable);
    dist[src] = 0;
    for (int round = 0; round < n - 1; ++round)
        for (auto [u, v, w] : edges)
            if (dist[u] != kUnreachable && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
    return dist;
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
    CHECK(dijkstra(4, build(4, {{0, 1, 4}, {0, 2, 1}, {2, 1, 2}, {1, 3, 5}}), 0) ==
          std::vector<long long>{0, 3, 1, 8});
    CHECK(dijkstra(3, build(3, {{0, 1, 7}}), 0) == std::vector<long long>{0, 7, kUnreachable});
    CHECK(dijkstra(3, build(3, {{0, 1, 1'000'000'000}, {1, 2, 1'000'000'000}, {2, 0, 0}}), 0) ==
          std::vector<long long>{0, 1'000'000'000, 2'000'000'000});
}

TEST_CASE("single vertex") {
    CHECK(dijkstra(1, build(1, {}), 0) == std::vector<long long>{0});
    CHECK(dijkstra(1, build(1, {{0, 0, 5}}), 0) == std::vector<long long>{0});
}

TEST_CASE("unreachable vertices") {
    // 0 -> 1 -> 2; vertices 3 and 4 only reach each other; vertex 5 is isolated.
    auto g = build(6, {{0, 1, 2}, {1, 2, 3}, {3, 4, 1}, {4, 3, 1}});
    CHECK(dijkstra(6, g, 0) == std::vector<long long>{0, 2, 5, kUnreachable, kUnreachable, kUnreachable});
    // Edges are directed: from vertex 2 nothing is reachable except itself.
    CHECK(dijkstra(6, g, 2) ==
          std::vector<long long>{kUnreachable, kUnreachable, 0, kUnreachable, kUnreachable, kUnreachable});
}

TEST_CASE("zero-weight edges") {
    auto g = build(5, {{0, 1, 0}, {1, 2, 0}, {0, 3, 4}, {2, 3, 1}, {3, 4, 0}});
    CHECK(dijkstra(5, g, 0) == std::vector<long long>{0, 0, 0, 1, 1});
    // A zero-weight cycle must not trap the search.
    auto h = build(3, {{0, 1, 0}, {1, 0, 0}, {1, 2, 3}});
    CHECK(dijkstra(3, h, 0) == std::vector<long long>{0, 0, 3});
}

TEST_CASE("parallel edges and self-loops") {
    auto g = build(3, {{0, 1, 9}, {0, 1, 2}, {0, 1, 5}, {1, 1, 1}, {1, 2, 4}, {1, 2, 3}, {0, 0, 0}});
    CHECK(dijkstra(3, g, 0) == std::vector<long long>{0, 2, 5});
}

TEST_CASE("path sums beyond INT_MAX") {
    // A chain of weight-10^9 edges: distances 0, 1e9, 2e9, 3e9, 4e9, 5e9.
    std::vector<Edge> edges;
    for (int i = 0; i < 5; ++i) edges.push_back({i, i + 1, 1'000'000'000});
    // A direct edge 0 -> 5 of weight 10^9 beats the 5*10^9 chain.
    edges.push_back({0, 5, 1'000'000'000});
    auto got = dijkstra(6, build(6, edges), 0);
    CHECK(got == std::vector<long long>{0, 1'000'000'000LL, 2'000'000'000LL, 3'000'000'000LL, 4'000'000'000LL,
                                        1'000'000'000LL});
    // Without the shortcut vertex 5 sits at 5e9, past INT_MAX.
    edges.pop_back();
    auto chain = dijkstra(6, build(6, edges), 0);
    REQUIRE(chain.size() == 6);
    CHECK(chain.back() == 5'000'000'000LL);
}

TEST_CASE("non-zero source") {
    auto g = build(4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 0, 1}});
    CHECK(dijkstra(4, g, 2) == std::vector<long long>{2, 3, 0, 1});
}

TEST_CASE("randomized vs Bellman-Ford") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 10);
        int m = rand_int(0, 30);
        std::vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            int w = rand_int(0, 3) == 0 ? 0 : rand_int(0, 20);
            if (rand_int(0, 9) == 0) w = rand_int(900'000'000, 1'000'000'000);
            edges.push_back({rand_int(0, n - 1), rand_int(0, n - 1), w});
        }
        int src = rand_int(0, n - 1);
        REQUIRE(dijkstra(n, build(n, edges), src) == bellmanFord(n, edges, src));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 vertices, 3*10^5 edges. A spine p[0] -> p[1] -> ... -> p[n-1] (p is a random relabeling) has
    // weights in [1, 10^4]; P[i] is the spine prefix sum. Every extra edge p[a] -> p[b] with a < b weighs
    // at least P[b] - P[a], so it never shortens anything, and every backward edge only leads to a
    // vertex whose spine distance is already smaller. Hence dist[p[i]] = P[i] exactly.
    const int n = 100'000, extra = 200'001;
    FastRng fr;
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    for (int i = n - 1; i > 0; --i) std::swap(p[i], p[fr.next(0, i)]);
    std::vector<long long> P(n, 0);
    WeightedGraph g(n);
    for (int i = 0; i + 1 < n; ++i) {
        int w = fr.next(1, 10'000);
        P[i + 1] = P[i] + w;
        g[p[i]].emplace_back(p[i + 1], w);
    }
    for (int e = 0; e < extra; ++e) {
        int a = fr.next(0, n - 1), b = fr.next(0, n - 1);
        if (a == b) continue;
        if (a < b) {
            g[p[a]].emplace_back(p[b], static_cast<int>(P[b] - P[a]) + fr.next(0, 1000));
        } else {
            g[p[a]].emplace_back(p[b], fr.next(0, 1'000'000'000));
        }
    }
    std::vector<long long> expected(n);
    for (int i = 0; i < n; ++i) expected[p[i]] = P[i];
    auto got = dijkstra(n, g, p[0]);
    REQUIRE(got.size() == static_cast<size_t>(n));
    CHECK(got == expected);
}
