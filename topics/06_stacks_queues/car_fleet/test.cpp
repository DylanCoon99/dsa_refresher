#include <car_fleet.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
// A car leads a fleet exactly when it arrives strictly later than every car that starts ahead of
// it. Arrival times are compared as exact fractions: (target-p_i)/s_i > (target-p_j)/s_j
// <=> (target-p_i)*s_j > (target-p_j)*s_i.
int brute(int target, const std::vector<int>& p, const std::vector<int>& s) {
    const int n = static_cast<int>(p.size());
    int fleets = 0;
    for (int i = 0; i < n; ++i) {
        bool leads = true;
        for (int j = 0; j < n; ++j) {
            if (p[j] > p[i] &&
                !(static_cast<long long>(target - p[i]) * s[j] > static_cast<long long>(target - p[j]) * s[i])) {
                leads = false;
                break;
            }
        }
        if (leads) ++fleets;
    }
    return fleets;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(carFleet(12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}) == 3);
    CHECK(carFleet(10, {0, 5}, {2, 1}) == 1);
    CHECK(carFleet(10, {8, 0}, {1, 4}) == 2);
    CHECK(carFleet(100, {0, 2, 4}, {4, 2, 1}) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("single car") { CHECK(carFleet(10, {3}, {3}) == 1); }
    SUBCASE("cars meeting exactly at the target are one fleet") {
        CHECK(carFleet(10, {0, 5}, {2, 1}) == 1);
        CHECK(carFleet(10, {0, 4, 7}, {10, 6, 3}) == 1);  // all arrive at time 1
    }
    SUBCASE("catching up only after the target does not merge") {
        CHECK(carFleet(10, {8, 0}, {1, 4}) == 2);
        CHECK(carFleet(10, {9, 0}, {1, 10}) == 1);  // times 1 and 1: tie at the target
        CHECK(carFleet(10, {9, 0}, {1, 9}) == 2);   // times 1 and 10/9: would catch up only after the target
        CHECK(carFleet(10, {9, 0}, {1, 11}) == 1);  // times 1 and 10/11: catches up before the target
    }
    SUBCASE("slower car behind never merges") {
        CHECK(carFleet(10, {5, 0}, {5, 1}) == 2);
        CHECK(carFleet(20, {6, 4, 2, 0}, {1, 1, 1, 1}) == 4);
    }
    SUBCASE("fast cars all behind one slow leader") { CHECK(carFleet(100, {50, 40, 30, 20, 10, 0}, {1, 9, 9, 9, 9, 9}) == 1); }
    SUBCASE("exact fractions: equal arrival times that are not representable in binary") {
        // (10-7)/3 = 1 and (10-4)/6 = 1; and 4/3 = 8/6 exactly.
        CHECK(carFleet(10, {7, 4}, {3, 6}) == 1);
        CHECK(carFleet(10, {6, 2}, {3, 6}) == 1);  // 4/3 and 8/6
        CHECK(carFleet(1'000'000, {999'999, 999'998}, {1, 2}) == 1);  // 1/1 and 2/2
        CHECK(carFleet(1'000'000, {999'999, 0}, {999'999, 1'000'000}) == 2);  // 1/999999 vs 1
    }
    SUBCASE("input order does not matter") {
        CHECK(carFleet(12, {0, 3, 5, 8, 10}, {1, 3, 1, 4, 2}) == 3);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        int target = rand_int(2, 30);
        int n = rand_int(1, std::min(target, 10));
        std::vector<int> pos(target);
        std::iota(pos.begin(), pos.end(), 0);
        std::shuffle(pos.begin(), pos.end(), rng());
        pos.resize(n);
        std::vector<int> speed = rand_vec(n, 1, 8);
        CAPTURE(target);
        CAPTURE(pos);
        CAPTURE(speed);
        CHECK(carFleet(target, pos, speed) == brute(target, pos, speed));
    }
}
