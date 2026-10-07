#include <sliding_window_max.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <set>
#include <vector>

namespace {
// O(n * k): scan every window.
std::vector<int> brute(const std::vector<int>& a, int k) {
    std::vector<int> out;
    for (std::size_t i = 0; i + k <= a.size(); ++i) out.push_back(*std::max_element(a.begin() + i, a.begin() + i + k));
    return out;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3) == std::vector<int>{3, 3, 5, 5, 6, 7});
    CHECK(maxSlidingWindow({1}, 1) == std::vector<int>{1});
    CHECK(maxSlidingWindow({9, 8, 7, 6}, 2) == std::vector<int>{9, 8, 7});
}

TEST_CASE("edge cases") {
    SUBCASE("k = 1 returns the array itself") {
        CHECK(maxSlidingWindow({4, -2, 7, 7, 0}, 1) == std::vector<int>{4, -2, 7, 7, 0});
    }
    SUBCASE("k = n gives one maximum") { CHECK(maxSlidingWindow({3, 9, -4, 6}, 4) == std::vector<int>{9}); }
    SUBCASE("decreasing input") {
        CHECK(maxSlidingWindow({9, 7, 5, 3, 1}, 3) == std::vector<int>{9, 7, 5});
    }
    SUBCASE("increasing input") {
        CHECK(maxSlidingWindow({1, 3, 5, 7, 9}, 3) == std::vector<int>{5, 7, 9});
    }
    SUBCASE("all negatives") {
        CHECK(maxSlidingWindow({-5, -3, -8, -1, -9}, 2) == std::vector<int>{-3, -3, -1, -1});
    }
    SUBCASE("all equal") { CHECK(maxSlidingWindow({2, 2, 2, 2}, 3) == std::vector<int>{2, 2}); }
    SUBCASE("maximum leaves the window") {
        CHECK(maxSlidingWindow({10, 1, 2, 3, 4}, 2) == std::vector<int>{10, 2, 3, 4});
    }
    SUBCASE("extreme values") {
        CHECK(maxSlidingWindow({-10'000, 10'000, -10'000}, 2) == std::vector<int>{10'000, 10'000});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::vector<int> a = rand_vec(rand_int(1, 30), -10, 10);
        const int k = rand_int(1, static_cast<int>(a.size()));
        CAPTURE(a);
        CAPTURE(k);
        CHECK(maxSlidingWindow(a, k) == brute(a, k));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 10^5 random values, k = 50000: 50001 windows of 50000 elements each, so scanning every
    // window is 2.5·10^9 steps. Expected output is built with a multiset (O(n log n)).
    const int n = 100'000, k = 50'000;
    std::mt19937 gen(2468);
    std::vector<int> a(n);
    for (int& v : a) v = static_cast<int>(gen() % 20001u) - 10'000;
    std::vector<int> expected;
    std::multiset<int> window(a.begin(), a.begin() + k);
    expected.push_back(*window.rbegin());
    for (int i = k; i < n; ++i) {
        window.erase(window.find(a[i - k]));
        window.insert(a[i]);
        expected.push_back(*window.rbegin());
    }
    const std::vector<int> got = maxSlidingWindow(a, k);
    REQUIRE(got.size() == expected.size());
    CHECK(got == expected);
}
