#include <koko_bananas.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
long long hours_at(const std::vector<int>& piles, long long k) {
    long long total = 0;
    for (int p : piles) total += (p + k - 1) / k;
    return total;
}
// Try every speed from 1 upward; only usable for small piles.
int brute(const std::vector<int>& piles, int h) {
    for (int k = 1;; ++k)
        if (hours_at(piles, k) <= h) return k;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minEatingSpeed({3, 6, 7, 11}, 8) == 4);
    CHECK(minEatingSpeed({30, 11, 23, 4, 20}, 5) == 30);
    CHECK(minEatingSpeed({30, 11, 23, 4, 20}, 6) == 23);
}

TEST_CASE("edge cases") {
    SUBCASE("h == n: answer is the largest pile") {
        CHECK(minEatingSpeed({5}, 1) == 5);
        CHECK(minEatingSpeed({2, 9, 4, 9, 1}, 5) == 9);
    }
    SUBCASE("huge h: speed 1 is enough") {
        CHECK(minEatingSpeed({1, 2, 3, 4}, 1'000'000'000) == 1);
        CHECK(minEatingSpeed({1'000'000'000}, 1'000'000'000) == 1);
    }
    SUBCASE("single pile") {
        CHECK(minEatingSpeed({10}, 3) == 4);   // ceil(10/4) = 3, ceil(10/3) = 4
        CHECK(minEatingSpeed({10}, 10) == 1);
    }
    SUBCASE("hour total at speed 1 overflows int") {
        // 3 piles of 10^9 at speed 1 need 3·10^9 hours.
        CHECK(minEatingSpeed({1'000'000'000, 1'000'000'000, 1'000'000'000}, 3) == 1'000'000'000);
        CHECK(minEatingSpeed({1'000'000'000, 1'000'000'000, 1'000'000'000}, 1'000'000'000) == 4);
        CHECK(minEatingSpeed(std::vector<int>(10'000, 1'000'000'000), 1'000'000'000) == 10'000);
    }
    SUBCASE("answer is exactly the boundary") {
        // 7 bananas, h = 4: speed 2 takes 4 hours, speed 1 takes 7.
        CHECK(minEatingSpeed({7}, 4) == 2);
        CHECK(minEatingSpeed({7}, 3) == 3);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const int n = rand_int(1, 8);
        const std::vector<int> piles = rand_vec(n, 1, 40);
        const int h = rand_int(n, 3 * n + 40);
        CHECK(minEatingSpeed(piles, h) == brute(piles, h));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^4 piles of 10^9 and h = n + 1: any speed below 10^9 needs two hours per pile (2n > n + 1),
    // so the answer is 10^9. Trying speeds 1, 2, 3, ... costs ~10^9 · n operations.
    const std::vector<int> piles(10'000, 1'000'000'000);
    CHECK(minEatingSpeed(piles, 10'001) == 1'000'000'000);
    // Same piles with h = 2n: speed 5·10^8 needs exactly two hours each.
    CHECK(minEatingSpeed(piles, 20'000) == 500'000'000);
}
