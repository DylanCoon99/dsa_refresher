#include <container_most_water.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <vector>

namespace {
int brute(const std::vector<int>& h) {
    int best = 0;
    const int n = static_cast<int>(h.size());
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) best = std::max(best, (j - i) * std::min(h[i], h[j]));
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
    CHECK(maxArea({1, 1}) == 1);
    CHECK(maxArea({4, 3, 2, 1, 4}) == 16);
}

TEST_CASE("edge cases") {
    SUBCASE("two walls") { CHECK(maxArea({3, 7}) == 3); }
    SUBCASE("two zero walls") { CHECK(maxArea({0, 0}) == 0); }
    SUBCASE("all zeros") { CHECK(maxArea(std::vector<int>(10, 0)) == 0); }
    SUBCASE("all equal") { CHECK(maxArea({5, 5, 5, 5, 5}) == 20); }
    SUBCASE("increasing") { CHECK(maxArea({1, 2, 3, 4, 5, 6}) == 9); }
    SUBCASE("decreasing") { CHECK(maxArea({6, 5, 4, 3, 2, 1}) == 9); }
    SUBCASE("best pair is adjacent") { CHECK(maxArea({0, 0, 9, 9, 0, 0}) == 9); }
    SUBCASE("one tall wall with short neighbours") { CHECK(maxArea({2, 100, 3, 2, 2, 2, 2, 2, 2, 2}) == 18); }
    SUBCASE("zero at an end") { CHECK(maxArea({0, 5, 5, 0}) == 5); }
    SUBCASE("maximum values") {
        std::vector<int> h(1000, 10000);
        CHECK(maxArea(h) == 999 * 10000);
    }
}

TEST_CASE("randomized vs O(n^2) brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> h = rand_vec(rand_int(2, 30), 0, 20);
        CHECK(maxArea(h) == brute(h));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 walls in [0, 5000] with 10000-high walls at both ends: the widest, tallest pair wins,
    // and an O(n^2) scan has to look at ~5·10^9 pairs.
    const int n = 100'000;
    std::mt19937 gen(2024);
    std::vector<int> h(n);
    for (int& v : h) v = static_cast<int>(gen() % 5001u);
    h.front() = h.back() = 10'000;
    CHECK(maxArea(h) == 10'000 * (n - 1));
}
