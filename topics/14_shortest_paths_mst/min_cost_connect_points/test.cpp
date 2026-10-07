#include <min_cost_connect_points.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>

namespace {
using Points = std::vector<std::vector<int>>;

int dist(const Points& p, int a, int b) { return std::abs(p[a][0] - p[b][0]) + std::abs(p[a][1] - p[b][1]); }

// Brute force: try every set of n - 1 edges and keep the cheapest one that connects all the points.
int brute(const Points& p) {
    int n = static_cast<int>(p.size());
    if (n == 1) return 0;
    std::vector<std::pair<int, int>> edges;
    for (int a = 0; a < n; ++a)
        for (int b = a + 1; b < n; ++b) edges.push_back({a, b});
    int m = static_cast<int>(edges.size());
    int best = 1'000'000'000;
    std::vector<bool> pick(m, false);
    std::fill(pick.begin(), pick.begin() + (n - 1), true);
    std::sort(pick.begin(), pick.end());  // false... then true...; iterate all combinations with next_permutation
    do {
        std::vector<int> label(n);
        for (int i = 0; i < n; ++i) label[i] = i;
        int cost = 0;
        for (int i = 0; i < m; ++i) {
            if (!pick[i]) continue;
            cost += dist(p, edges[i].first, edges[i].second);
            int from = label[edges[i].first], to = label[edges[i].second];
            for (int& x : label)
                if (x == from) x = to;
        }
        bool connected = true;
        for (int i = 0; i < n; ++i) connected = connected && label[i] == label[0];
        if (connected) best = std::min(best, cost);
    } while (std::next_permutation(pick.begin(), pick.end()));
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minCostConnectPoints({{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}) == 20);
    CHECK(minCostConnectPoints({{3, 12}, {-2, 5}, {-4, 1}}) == 18);
    CHECK(minCostConnectPoints({{5, 5}}) == 0);
}

TEST_CASE("single point") {
    CHECK(minCostConnectPoints({{0, 0}}) == 0);
    CHECK(minCostConnectPoints({{-1'000'000, 1'000'000}}) == 0);
}

TEST_CASE("two points") {
    CHECK(minCostConnectPoints({{0, 0}, {3, 4}}) == 7);
    CHECK(minCostConnectPoints({{-5, -5}, {5, 5}}) == 20);
    CHECK(minCostConnectPoints({{-1'000'000, -1'000'000}, {1'000'000, 1'000'000}}) == 4'000'000);
}

TEST_CASE("collinear points") {
    // On a line the cheapest tree is the chain of neighbours: total = max - min.
    CHECK(minCostConnectPoints({{0, 0}, {5, 0}, {2, 0}, {9, 0}}) == 9);
    CHECK(minCostConnectPoints({{4, -3}, {4, 10}, {4, 0}, {4, 2}}) == 13);
    CHECK(minCostConnectPoints({{0, 0}, {1, 1}, {2, 2}, {3, 3}}) == 6);
}

TEST_CASE("a square") {
    CHECK(minCostConnectPoints({{0, 0}, {0, 10}, {10, 0}, {10, 10}}) == 30);
}

TEST_CASE("randomized vs spanning-tree enumeration") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 6);
        std::set<std::pair<int, int>> used;
        Points p;
        while (static_cast<int>(p.size()) < n) {
            int x = rand_int(-10, 10), y = rand_int(-10, 10);
            if (used.insert({x, y}).second) p.push_back({x, y});
        }
        REQUIRE(minCostConnectPoints(p) == brute(p));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 1000 points on a 25 x 40 lattice with spacing 1000, in shuffled order. Every lattice neighbour is
    // exactly 1000 away and every other pair is farther, so a spanning tree of 999 edges of length 1000
    // is optimal: the answer is 999 * 1000.
    const int spacing = 1000, w = 25, h = 40;
    int ox = rand_int(-500'000, -1000), oy = rand_int(-500'000, -1000);
    Points p;
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) p.push_back({ox + i * spacing, oy + j * spacing});
    std::shuffle(p.begin(), p.end(), rng());
    REQUIRE(p.size() == 1000);
    CHECK(minCostConnectPoints(p) == 999 * spacing);
}
