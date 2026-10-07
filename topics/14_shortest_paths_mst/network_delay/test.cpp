#include <network_delay.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
using Times = std::vector<std::vector<int>>;

// Brute force: Floyd-Warshall over all pairs, then the largest distance from k.
int brute(const Times& times, int n, int k) {
    const long long INF = 1'000'000'000'000LL;
    std::vector<std::vector<long long>> d(n + 1, std::vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; ++i) d[i][i] = 0;
    for (const auto& t : times) d[t[0]][t[1]] = std::min<long long>(d[t[0]][t[1]], t[2]);
    for (int m = 1; m <= n; ++m)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) d[i][j] = std::min(d[i][j], d[i][m] + d[m][j]);
    long long worst = 0;
    for (int v = 1; v <= n; ++v) worst = std::max(worst, d[k][v]);
    return worst >= INF ? -1 : static_cast<int>(worst);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(networkDelayTime({{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2) == 2);
    CHECK(networkDelayTime({{1, 2, 1}}, 2, 1) == 1);
    CHECK(networkDelayTime({{1, 2, 1}}, 2, 2) == -1);
}

TEST_CASE("single node") {
    CHECK(networkDelayTime({}, 1, 1) == 0);
}

TEST_CASE("unreachable nodes") {
    CHECK(networkDelayTime({}, 3, 1) == -1);
    CHECK(networkDelayTime({{1, 2, 5}, {3, 2, 1}}, 3, 1) == -1);  // node 3 only has an outgoing link
    CHECK(networkDelayTime({{1, 2, 1}, {2, 1, 1}, {3, 4, 1}}, 4, 1) == -1);
}

TEST_CASE("multiple paths") {
    // 1 -> 2 -> 3 costs 2 but 1 -> 3 costs 10; the faster route wins.
    CHECK(networkDelayTime({{1, 2, 1}, {2, 3, 1}, {1, 3, 10}}, 3, 1) == 2);
    // Fewer hops is not faster: 1 -> 4 directly costs 9, the three-hop route costs 3.
    CHECK(networkDelayTime({{1, 4, 9}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 1) == 3);
    // The answer is the farthest node, not the sum.
    CHECK(networkDelayTime({{1, 2, 4}, {1, 3, 7}, {1, 4, 2}}, 4, 1) == 7);
}

TEST_CASE("zero-weight links and parallel links") {
    CHECK(networkDelayTime({{1, 2, 0}, {2, 3, 0}}, 3, 1) == 0);
    CHECK(networkDelayTime({{1, 2, 9}, {1, 2, 3}, {1, 2, 6}}, 2, 1) == 3);
}

TEST_CASE("links are directed") {
    CHECK(networkDelayTime({{1, 2, 1}, {2, 3, 1}}, 3, 3) == -1);
    CHECK(networkDelayTime({{1, 2, 1}, {2, 3, 1}, {3, 1, 1}}, 3, 3) == 2);
}

TEST_CASE("randomized vs Floyd-Warshall") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 8);
        int m = rand_int(0, 20);
        Times times;
        for (int i = 0; i < m && n > 1; ++i) {
            int u = rand_int(1, n), v = rand_int(1, n);
            if (u == v) continue;
            times.push_back({u, v, rand_int(0, 9)});
        }
        int k = rand_int(1, n);
        REQUIRE(networkDelayTime(times, n, k) == brute(times, n, k));
    }
}
