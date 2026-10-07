#include <largest_rectangle_histogram.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
int brute(const std::vector<int>& h) {
    const int n = static_cast<int>(h.size());
    int best = 0;
    for (int l = 0; l < n; ++l) {
        int mn = h[l];
        for (int r = l; r < n; ++r) {
            mn = std::min(mn, h[r]);
            best = std::max(best, mn * (r - l + 1));
        }
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(largestRectangleArea({2, 1, 5, 6, 2, 3}) == 10);
    CHECK(largestRectangleArea({2, 4}) == 4);
    CHECK(largestRectangleArea({3, 0, 3, 3}) == 6);
}

TEST_CASE("edge cases") {
    SUBCASE("single bar") { CHECK(largestRectangleArea({7}) == 7); }
    SUBCASE("single zero bar") { CHECK(largestRectangleArea({0}) == 0); }
    SUBCASE("all equal") { CHECK(largestRectangleArea({4, 4, 4, 4}) == 16); }
    SUBCASE("increasing") { CHECK(largestRectangleArea({1, 2, 3, 4, 5}) == 9); }
    SUBCASE("decreasing") { CHECK(largestRectangleArea({5, 4, 3, 2, 1}) == 9); }
    SUBCASE("zeros split the histogram") {
        CHECK(largestRectangleArea({0, 0}) == 0);
        CHECK(largestRectangleArea({0, 5, 0}) == 5);
        CHECK(largestRectangleArea({2, 0, 2, 2, 0, 2, 2, 2}) == 6);
    }
    SUBCASE("valley: widest rectangle uses the lowest bar") { CHECK(largestRectangleArea({6, 1, 6}) == 6); }
    SUBCASE("rectangle ending at the last bar") { CHECK(largestRectangleArea({1, 3, 3, 3}) == 9); }
    SUBCASE("maximum heights") {
        CHECK(largestRectangleArea(std::vector<int>(1000, 10'000)) == 10'000'000);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> h = rand_vec(rand_int(1, 25), 0, rand_int(1, 15));
        CAPTURE(h);
        CHECK(largestRectangleArea(h) == brute(h));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 bars of height 1: the answer is the whole width. Expanding from every bar costs ~10^10 steps.
    const int n = 100'000;
    CHECK(largestRectangleArea(std::vector<int>(n, 1)) == n);
}
