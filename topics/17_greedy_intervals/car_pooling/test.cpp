#include <car_pooling.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

using Trips = std::vector<std::vector<int>>;

namespace {
// Count the load at every integer position x in [0, range): the trips with from <= x < to.
bool brute(const Trips& trips, int capacity, int range) {
    for (int x = 0; x < range; ++x) {
        int load = 0;
        for (const auto& t : trips)
            if (t[1] <= x && x < t[2]) load += t[0];
        if (load > capacity) return false;
    }
    return true;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(carPooling({{2, 1, 5}, {3, 3, 7}}, 4) == false);
    CHECK(carPooling({{2, 1, 5}, {3, 3, 7}}, 5) == true);
    CHECK(carPooling({{3, 2, 7}, {3, 7, 9}}, 3) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("no trips") { CHECK(carPooling({}, 1) == true); }
    SUBCASE("a single trip within capacity") { CHECK(carPooling({{4, 0, 10}}, 4) == true); }
    SUBCASE("a single trip over capacity") {
        CHECK(carPooling({{5, 0, 10}}, 4) == false);
        CHECK(carPooling({{2, 3, 4}}, 1) == false);
    }
    SUBCASE("drop-off and pick-up at the same point stay within capacity") {
        CHECK(carPooling({{3, 2, 7}, {3, 7, 9}}, 3) == true);
        CHECK(carPooling({{3, 7, 9}, {3, 2, 7}}, 3) == true);  // given in the other order
        CHECK(carPooling({{5, 1, 4}, {5, 4, 8}, {5, 8, 9}}, 5) == true);
    }
    SUBCASE("overlap of one position is over capacity") {
        CHECK(carPooling({{3, 2, 8}, {3, 7, 9}}, 5) == false);
    }
    SUBCASE("exactly at capacity is fine") { CHECK(carPooling({{2, 0, 5}, {3, 1, 4}}, 5) == true); }
    SUBCASE("a drop-off at the same point as a pick-up with a third trip running") {
        // At position 5: 2 leave, 4 board, 3 stay on. The load is 3 + 2 = 5 before and 3 + 4 = 7 after.
        CHECK(carPooling({{3, 0, 10}, {2, 1, 5}, {4, 5, 9}}, 7) == true);
        CHECK(carPooling({{3, 0, 10}, {2, 1, 5}, {4, 5, 9}}, 6) == false);
    }
    SUBCASE("trips far apart on the road") {
        CHECK(carPooling({{50, 0, 1}, {50, 1000000000 - 1, 1000000000}}, 50) == true);
    }
    SUBCASE("unsorted trips") { CHECK(carPooling({{4, 6, 8}, {1, 0, 9}, {3, 2, 7}}, 7) == false); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const int n = rand_int(1, 8);
        Trips trips;
        for (int i = 0; i < n; ++i) {
            const int from = rand_int(0, 15);
            trips.push_back({rand_int(1, 5), from, from + rand_int(1, 6)});
        }
        const int capacity = rand_int(1, 12);
        INFO("trial " << trial << " capacity=" << capacity);
        CHECK(carPooling(trips, capacity) == brute(trips, capacity, 25));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Trip i carries 1 passenger over [9999 i, 9999 i + 19998): each trip overlaps only its two
    // neighbours, so at most 2 passengers are ever on board. The last position is
    // 9999 * 99999 + 19998 = 999909999 <= 10^9.
    const int n = 100000;
    Trips trips;
    for (int i = 0; i < n; ++i) trips.push_back({1, 9999 * i, 9999 * i + 19998});
    std::shuffle(trips.begin(), trips.end(), rng());
    CHECK(carPooling(trips, 2) == true);
    CHECK(carPooling(trips, 1) == false);
}
