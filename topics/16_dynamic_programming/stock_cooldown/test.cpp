#include <stock_cooldown.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// best(i) = best profit from days i.. when not holding and free to buy. Either skip day i, or buy on day i and
// sell on some later day j; the next purchase is then allowed from day j + 2. Exponential, fine for n <= 12.
int best(const std::vector<int>& p, std::size_t i) {
    int result = 0;
    for (std::size_t b = i; b < p.size(); ++b)
        for (std::size_t s = b + 1; s < p.size(); ++s)
            result = std::max(result, p[s] - p[b] + best(p, s + 2));
    return result;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxProfit({1, 2, 3, 0, 2}) == 3);
    CHECK(maxProfit({1}) == 0);
    CHECK(maxProfit({5, 4, 3, 2, 1}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("a single day") {
        CHECK(maxProfit({7}) == 0);
        CHECK(maxProfit({0}) == 0);
    }
    SUBCASE("decreasing prices") { CHECK(maxProfit({9, 7, 5, 3}) == 0); }
    SUBCASE("two days") {
        CHECK(maxProfit({1, 5}) == 4);
        CHECK(maxProfit({5, 1}) == 0);
    }
    SUBCASE("flat prices") { CHECK(maxProfit({3, 3, 3, 3}) == 0); }
    SUBCASE("steadily rising: one long hold beats cooldown-limited trades") { CHECK(maxProfit({1, 2, 3, 4, 5}) == 4); }
    SUBCASE("the cooldown forces a skipped day") {
        // Without a cooldown: 1->2, 2->3 would be allowed back-to-back; the cooldown changes the plan.
        CHECK(maxProfit({1, 4, 2, 7}) == 6);
        CHECK(maxProfit({2, 1, 4}) == 3);
    }
    SUBCASE("zigzag") { CHECK(maxProfit({1, 2, 1, 2, 1, 2}) == 2); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> prices = rand_vec(rand_int(1, 11), 0, 10);
        INFO(prices);
        CHECK(maxProfit(prices) == best(prices, 0));
    }
}
