#include <min_arrows.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

using Points = std::vector<std::vector<int>>;

namespace {
// Spans use small codes 0..9. An arrow can be placed at any code; try every subset of the 10 codes
// and keep the smallest one that hits every span (a span {a,b} is hit iff an arrow code is in [a,b]).
int brute(const Points& v) {
    int best = static_cast<int>(v.size());
    for (int mask = 0; mask < (1 << 10); ++mask) {
        bool ok = true;
        for (const auto& p : v) {
            bool hit = false;
            for (int c = p[0]; c <= p[1]; ++c)
                if (mask >> c & 1) hit = true;
            if (!hit) {
                ok = false;
                break;
            }
        }
        if (ok) best = std::min(best, __builtin_popcount(mask));
    }
    return best;
}

// Order-preserving map of codes 0..9 onto extreme coordinates: 0..4 near INT_MIN, 5..9 near INT_MAX.
// Equal codes stay equal and the order is unchanged, so the answer is the same, but differences
// between far-apart coordinates overflow int.
int extreme(int code) { return code < 5 ? INT_MIN + code : INT_MAX - 9 + code; }
}  // namespace

TEST_CASE("examples") {
    CHECK(findMinArrowShots({{10, 16}, {2, 8}, {1, 6}, {7, 12}}) == 2);
    CHECK(findMinArrowShots({{1, 2}, {3, 4}, {5, 6}, {7, 8}}) == 4);
    CHECK(findMinArrowShots({{1, 2}, {2, 3}, {3, 4}, {4, 5}}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(findMinArrowShots({}) == 0); }
    SUBCASE("single balloon") { CHECK(findMinArrowShots({{3, 9}}) == 1); }
    SUBCASE("touching balloons share one arrow (closed)") {
        CHECK(findMinArrowShots({{1, 2}, {2, 3}}) == 1);
        CHECK(findMinArrowShots({{2, 3}, {1, 2}}) == 1);
    }
    SUBCASE("a gap of one needs two arrows") { CHECK(findMinArrowShots({{1, 2}, {3, 4}}) == 2); }
    SUBCASE("identical balloons") { CHECK(findMinArrowShots(Points(5, {4, 4})) == 1); }
    SUBCASE("nested balloons") { CHECK(findMinArrowShots({{1, 10}, {2, 9}, {3, 8}}) == 1); }
    SUBCASE("full int range: one balloon") {
        CHECK(findMinArrowShots({{INT_MIN, INT_MAX}}) == 1);
    }
    SUBCASE("full int range: two far-apart point balloons") {
        CHECK(findMinArrowShots({{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}}) == 2);
        CHECK(findMinArrowShots({{INT_MAX, INT_MAX}, {INT_MIN, INT_MIN}}) == 2);
    }
    SUBCASE("full int range: wide balloons that overlap") {
        CHECK(findMinArrowShots({{INT_MIN, 0}, {0, INT_MAX}, {INT_MIN, INT_MAX}}) == 1);
        CHECK(findMinArrowShots({{INT_MIN, -1}, {1, INT_MAX}}) == 2);
    }
    SUBCASE("full int range: negative to positive, reversed order") {
        CHECK(findMinArrowShots({{INT_MAX - 1, INT_MAX}, {INT_MIN, INT_MIN + 1}, {INT_MIN + 1, 5}}) == 2);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 8);
        Points codes;
        for (int i = 0; i < n; ++i) {
            int a = rand_int(0, 9), b = rand_int(0, 9);
            if (a > b) std::swap(a, b);
            codes.push_back({a, b});
        }
        const int expected = brute(codes);
        INFO("trial " << trial);
        CHECK(findMinArrowShots(codes) == expected);
        Points wide;
        for (const auto& c : codes) wide.push_back({extreme(c[0]), extreme(c[1])});
        CHECK(findMinArrowShots(wide) == expected);
    }
}
