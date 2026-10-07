#include <cheapest_flights_k_stops.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
using Flights = std::vector<std::vector<int>>;

// Brute force: depth-first search over every route of at most k + 1 flights (cities may repeat).
void dfs(const Flights& flights, int at, int dst, int flightsLeft, int cost, int& best) {
    if (at == dst) best = std::min(best, cost);
    if (flightsLeft == 0) return;
    for (const auto& f : flights)
        if (f[0] == at) dfs(flights, f[1], dst, flightsLeft - 1, cost + f[2], best);
}

int brute(const Flights& flights, int src, int dst, int k) {
    int best = 1'000'000'000;
    dfs(flights, src, dst, k + 1, 0, best);
    return best == 1'000'000'000 ? -1 : best;
}
}  // namespace

TEST_CASE("examples") {
    Flights a{{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    CHECK(findCheapestPrice(4, a, 0, 3, 1) == 700);
    Flights b{{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    CHECK(findCheapestPrice(3, b, 0, 2, 1) == 200);
    CHECK(findCheapestPrice(3, b, 0, 2, 0) == 500);
}

TEST_CASE("the cheapest path has too many stops") {
    // 0 -> 1 -> 2 -> 3 -> 4 costs 4 (3 stops); the direct flight costs 100.
    Flights f{{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {0, 4, 100}};
    CHECK(findCheapestPrice(5, f, 0, 4, 0) == 100);
    CHECK(findCheapestPrice(5, f, 0, 4, 1) == 100);
    CHECK(findCheapestPrice(5, f, 0, 4, 2) == 100);
    CHECK(findCheapestPrice(5, f, 0, 4, 3) == 4);
    CHECK(findCheapestPrice(5, f, 0, 4, 4) == 4);
    // A middle option: 0 -> 2 -> 4 costs 20 with one stop.
    Flights g{{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {0, 2, 10}, {2, 4, 10}, {0, 4, 100}};
    CHECK(findCheapestPrice(5, g, 0, 4, 1) == 20);
    CHECK(findCheapestPrice(5, g, 0, 4, 2) == 12);  // 0 -> 1 -> 2 -> 4
    CHECK(findCheapestPrice(5, g, 0, 4, 3) == 4);
}

TEST_CASE("k = 0 allows only a direct flight") {
    Flights f{{0, 1, 5}, {1, 2, 5}, {0, 2, 50}};
    CHECK(findCheapestPrice(3, f, 0, 2, 0) == 50);
    CHECK(findCheapestPrice(3, f, 0, 1, 0) == 5);
    CHECK(findCheapestPrice(3, {{0, 1, 5}, {1, 2, 5}}, 0, 2, 0) == -1);
}

TEST_CASE("unreachable") {
    CHECK(findCheapestPrice(3, {}, 0, 2, 2) == -1);
    CHECK(findCheapestPrice(3, {{2, 0, 1}, {1, 2, 1}}, 0, 2, 2) == -1);  // flights point the wrong way
    CHECK(findCheapestPrice(4, {{0, 1, 1}, {2, 3, 1}}, 0, 3, 3) == -1);
}

TEST_CASE("stop-limit trap") {
    // Dijkstra on price alone settles city 2 through 0 -> 1 -> 2 (cost 2, already one stop used),
    // then extends to city 3 using a second stop. With k = 1 the valid answer is 0 -> 2 -> 3.
    Flights f{{0, 1, 1}, {1, 2, 1}, {0, 2, 5}, {2, 3, 1}};
    CHECK(findCheapestPrice(4, f, 0, 3, 1) == 6);
    CHECK(findCheapestPrice(4, f, 0, 3, 2) == 3);
    CHECK(findCheapestPrice(4, f, 0, 3, 0) == -1);
}

TEST_CASE("cycles do not help") {
    Flights f{{0, 1, 1}, {1, 0, 1}, {1, 2, 1}};
    CHECK(findCheapestPrice(3, f, 0, 2, 5) == 2);
}

TEST_CASE("randomized vs enumeration") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(2, 6);
        Flights flights;
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v)
                if (u != v && rand_int(0, 2) == 0) flights.push_back({u, v, rand_int(1, 20)});
        int src = rand_int(0, n - 1), dst = rand_int(0, n - 1);
        if (src == dst) dst = (src + 1) % n;
        int k = rand_int(0, n - 1);
        REQUIRE(findCheapestPrice(n, flights, src, dst, k) == brute(flights, src, dst, k));
    }
}
