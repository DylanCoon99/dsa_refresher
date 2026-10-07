#include <max_overlap.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <utility>
#include <vector>

using Iv = std::vector<std::pair<int, int>>;

namespace {
// The maximum is always reached at some start point, so count the intervals containing each start.
int brute(const Iv& in) {
    int best = 0;
    for (const auto& p : in) {
        int cnt = 0;
        for (const auto& q : in)
            if (q.first <= p.first && p.first < q.second) ++cnt;
        best = std::max(best, cnt);
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxOverlap({{1, 4}, {2, 5}, {3, 6}}) == 3);
    CHECK(maxOverlap({{1, 3}, {3, 5}}) == 1);
    CHECK(maxOverlap({{1, 10}, {2, 3}, {4, 5}}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(maxOverlap({}) == 0); }
    SUBCASE("single interval") { CHECK(maxOverlap({{5, 9}}) == 1); }
    SUBCASE("touching intervals do not overlap") {
        CHECK(maxOverlap({{1, 2}, {2, 3}, {3, 4}, {4, 5}}) == 1);
        CHECK(maxOverlap({{3, 5}, {1, 3}}) == 1);
    }
    SUBCASE("identical intervals") {
        CHECK(maxOverlap({{2, 7}, {2, 7}, {2, 7}, {2, 7}}) == 4);
        CHECK(maxOverlap({{0, 1}, {0, 1}}) == 2);
    }
    SUBCASE("nested intervals") { CHECK(maxOverlap({{1, 10}, {2, 9}, {3, 8}, {4, 7}}) == 4); }
    SUBCASE("unsorted input") { CHECK(maxOverlap({{6, 9}, {1, 4}, {3, 7}, {2, 5}}) == 3); }
    SUBCASE("an end and a start at the same time with others active") {
        // At time 4: {1,4} ends and {4,8} starts; {2,6} stays, so the count there is 2, never 3.
        CHECK(maxOverlap({{1, 4}, {4, 8}, {2, 6}}) == 2);
    }
    SUBCASE("large coordinates") { CHECK(maxOverlap({{0, 1000000000}, {999999999, 1000000000}}) == 2); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 10);
        Iv in;
        for (int i = 0; i < n; ++i) {
            const int a = rand_int(0, 15);
            in.push_back({a, a + rand_int(1, 6)});
        }
        INFO("trial " << trial);
        CHECK(maxOverlap(in) == brute(in));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // [i, i + h) for i = 0..n-1. A point p in [0, n-1] is covered by min(p + 1, h) of them,
    // so the maximum is h (reached from p = h - 1 on).
    const int n = 100000, h = 50000;
    Iv in;
    for (int i = 0; i < n; ++i) in.push_back({i, i + h});
    std::shuffle(in.begin(), in.end(), rng());
    CHECK(maxOverlap(in) == h);

    // Back-to-back intervals touch but never overlap.
    Iv chain;
    for (int i = 0; i < n; ++i) chain.push_back({2 * i, 2 * i + 2});
    std::shuffle(chain.begin(), chain.end(), rng());
    CHECK(maxOverlap(chain) == 1);
}
