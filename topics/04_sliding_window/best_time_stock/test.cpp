#include <best_time_stock.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <vector>

namespace {
int brute(const std::vector<int>& p) {
    int best = 0;
    for (std::size_t i = 0; i < p.size(); ++i)
        for (std::size_t j = i + 1; j < p.size(); ++j) best = std::max(best, p[j] - p[i]);
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxProfit({7, 1, 5, 3, 6, 4}) == 5);
    CHECK(maxProfit({7, 6, 4, 3, 1}) == 0);
    CHECK(maxProfit({2, 4, 1}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("single day") { CHECK(maxProfit({5}) == 0); }
    SUBCASE("strictly decreasing") { CHECK(maxProfit({9, 8, 7, 6, 5, 4, 3}) == 0); }
    SUBCASE("all equal") { CHECK(maxProfit({3, 3, 3, 3}) == 0); }
    SUBCASE("two days up") { CHECK(maxProfit({1, 2}) == 1); }
    SUBCASE("two days down") { CHECK(maxProfit({2, 1}) == 0); }
    SUBCASE("lowest price comes after the highest") { CHECK(maxProfit({10, 11, 1}) == 1); }
    SUBCASE("best trade does not use the global minimum") { CHECK(maxProfit({5, 10, 1, 4}) == 5); }
    SUBCASE("zero price and the maximum price") { CHECK(maxProfit({0, 10'000}) == 10'000); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::vector<int> p = rand_vec(rand_int(1, 30), 0, 40);
        CAPTURE(p);
        CHECK(maxProfit(p) == brute(p));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 prices in [1, 9999], with a price of 0 on day 20000 and 10000 on day 80000.
    // The best trade is exactly that pair; checking all pairs is ~5·10^9 steps.
    const int n = 100'000;
    std::mt19937 gen(31337);
    std::vector<int> p(n);
    for (int& v : p) v = 1 + static_cast<int>(gen() % 9999u);
    p[20'000] = 0;
    p[80'000] = 10'000;
    CHECK(maxProfit(p) == 10'000);
}
