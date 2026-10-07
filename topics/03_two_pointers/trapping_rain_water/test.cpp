#include <trapping_rain_water.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// Per-index scan: water above i = min(max to the left, max to the right) - height[i].
int brute(const std::vector<int>& h) {
    int total = 0;
    const int n = static_cast<int>(h.size());
    for (int i = 0; i < n; ++i) {
        int left = 0, right = 0;
        for (int k = 0; k <= i; ++k) left = std::max(left, h[k]);
        for (int k = i; k < n; ++k) right = std::max(right, h[k]);
        total += std::min(left, right) - h[i];
    }
    return total;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6);
    CHECK(trap({4, 2, 0, 3, 2, 5}) == 9);
    CHECK(trap({1, 2, 3}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(trap({}) == 0); }
    SUBCASE("single bar") { CHECK(trap({5}) == 0); }
    SUBCASE("two bars") { CHECK(trap({5, 3}) == 0); }
    SUBCASE("strictly increasing") { CHECK(trap({1, 2, 3, 4, 5}) == 0); }
    SUBCASE("strictly decreasing") { CHECK(trap({5, 4, 3, 2, 1}) == 0); }
    SUBCASE("all equal") { CHECK(trap({3, 3, 3, 3}) == 0); }
    SUBCASE("all zeros") { CHECK(trap({0, 0, 0}) == 0); }
    SUBCASE("a single valley") { CHECK(trap({3, 0, 3}) == 3); }
    SUBCASE("a wide valley") { CHECK(trap({5, 1, 1, 1, 4}) == 9); }
    SUBCASE("uneven walls, the lower one limits") { CHECK(trap({2, 0, 0, 7}) == 4); }
    SUBCASE("two valleys") { CHECK(trap({3, 0, 2, 0, 3}) == 7); }
    SUBCASE("valley next to a taller far wall") { CHECK(trap({1, 0, 1, 0, 9}) == 2); }
    SUBCASE("large heights") { CHECK(trap({100000, 0, 100000}) == 100000); }
}

TEST_CASE("randomized vs per-index brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> h = rand_vec(rand_int(0, 30), 0, 12);
        CHECK(trap(h) == brute(h));
    }
}
