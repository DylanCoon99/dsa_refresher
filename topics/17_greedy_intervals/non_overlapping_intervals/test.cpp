#include <non_overlapping_intervals.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

using Intervals = std::vector<std::vector<int>>;

namespace {
// Try every subset, keep the largest one whose members pairwise do not overlap (half-open),
// and return n minus its size. Fine for n <= 12.
int brute(const Intervals& v) {
    const int n = static_cast<int>(v.size());
    int bestKept = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            if (!(mask >> i & 1)) continue;
            for (int j = i + 1; j < n && ok; ++j) {
                if (!(mask >> j & 1)) continue;
                if (v[i][0] < v[j][1] && v[j][0] < v[i][1]) ok = false;
            }
        }
        if (ok) bestKept = std::max(bestKept, __builtin_popcount(mask));
    }
    return n - bestKept;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(eraseOverlapIntervals({{1, 2}, {2, 3}, {3, 4}, {1, 3}}) == 1);
    CHECK(eraseOverlapIntervals({{1, 2}, {1, 2}, {1, 2}}) == 2);
    CHECK(eraseOverlapIntervals({{1, 2}, {2, 3}}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(eraseOverlapIntervals({}) == 0); }
    SUBCASE("single interval") { CHECK(eraseOverlapIntervals({{4, 9}}) == 0); }
    SUBCASE("touching intervals both stay") {
        CHECK(eraseOverlapIntervals({{1, 2}, {2, 3}}) == 0);
        CHECK(eraseOverlapIntervals({{3, 4}, {1, 2}, {2, 3}}) == 0);
    }
    SUBCASE("all identical removes n - 1") {
        CHECK(eraseOverlapIntervals(Intervals(7, {5, 8})) == 6);
        CHECK(eraseOverlapIntervals({{1, 2}, {1, 2}}) == 1);
    }
    SUBCASE("nested intervals: remove the big one") {
        CHECK(eraseOverlapIntervals({{1, 10}, {2, 3}, {4, 5}, {6, 7}}) == 1);
    }
    SUBCASE("nested chain") { CHECK(eraseOverlapIntervals({{1, 10}, {2, 9}, {3, 8}, {4, 7}}) == 3); }
    SUBCASE("unsorted input") { CHECK(eraseOverlapIntervals({{5, 6}, {1, 3}, {2, 4}, {3, 5}}) == 1); }
    SUBCASE("earliest start is the wrong greedy key") {
        // Sorting by start and keeping {0,100} first would keep 1 interval; the best keeps 3.
        CHECK(eraseOverlapIntervals({{0, 100}, {1, 2}, {3, 4}, {5, 6}}) == 1);
    }
    SUBCASE("shortest first is the wrong greedy key") {
        // {4,7} is the shortest but overlaps both {1,5} and {6,10}, which do not overlap each other:
        // keeping the shortest first keeps 1, the best keeps 2.
        CHECK(eraseOverlapIntervals({{1, 5}, {4, 7}, {6, 10}}) == 1);
    }
    SUBCASE("large coordinates") {
        CHECK(eraseOverlapIntervals({{0, 1000000000}, {0, 500000000}, {500000000, 1000000000}}) == 1);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 200; ++trial) {
        const int n = rand_int(1, 11);
        Intervals in;
        for (int i = 0; i < n; ++i) {
            const int a = rand_int(0, 12);
            in.push_back({a, a + rand_int(1, 5)});
        }
        INFO("trial " << trial);
        CHECK(eraseOverlapIntervals(in) == brute(in));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    const int n = 100000;
    // {i, i+2}: neighbours overlap, i and i+2 touch. The most that can be kept is every other one
    // (0-2, 2-4, ...): n/2 = 50000, so n/2 = 50000 are removed.
    Intervals chain;
    for (int i = 0; i < n; ++i) chain.push_back({i, i + 2});
    std::shuffle(chain.begin(), chain.end(), rng());
    CHECK(eraseOverlapIntervals(chain) == n / 2);

    // All identical: keep one, remove n - 1.
    CHECK(eraseOverlapIntervals(Intervals(n, {7, 9})) == n - 1);
}
