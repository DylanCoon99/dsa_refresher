#include <coin_change_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
// Count combinations by deciding, coin by coin, how many copies to use. Obviously correct; exponential.
int brute(int amount, const std::vector<int>& coins, std::size_t i = 0) {
    if (amount == 0) return 1;
    if (i == coins.size()) return 0;
    int total = 0;
    for (int used = 0; used * coins[i] <= amount; ++used) total += brute(amount - used * coins[i], coins, i + 1);
    return total;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(change(5, {1, 2, 5}) == 4);
    CHECK(change(3, {2}) == 0);
    CHECK(change(3, {1, 2}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("amount 0 has one combination") {
        CHECK(change(0, {1, 2}) == 1);
        CHECK(change(0, {7}) == 1);
    }
    SUBCASE("no way") {
        CHECK(change(7, {2, 4}) == 0);
        CHECK(change(3, {5, 10}) == 0);
    }
    SUBCASE("the order of coins does not create duplicates") {
        CHECK(change(3, {1, 2}) == 2);
        CHECK(change(3, {2, 1}) == 2);
        CHECK(change(4, {1, 2, 3}) == 4);
    }
    SUBCASE("a single coin") {
        CHECK(change(10, {10}) == 1);
        CHECK(change(10, {5}) == 1);
        CHECK(change(10, {3}) == 0);
    }
    SUBCASE("coin order does not matter") {
        CHECK(change(10, {5, 2, 1}) == change(10, {1, 2, 5}));
    }
    SUBCASE("coins larger than the amount are ignored") { CHECK(change(4, {1, 100}) == 1); }
    SUBCASE("1, 2, ..., 10 into 50 (exact count, a few thousand combinations)") {
        std::vector<int> coins(10);
        std::iota(coins.begin(), coins.end(), 1);
        CHECK(change(50, coins) == 62740);
    }
}

TEST_CASE("intermediate table values can exceed int") {
    // Even coins 2, 4, ..., 40: the table entry for amount 998 is about 2e17, far beyond a 32-bit int
    // (but within long long). The odd amount 999 has no combination, so the answer is 0.
    std::vector<int> evens;
    for (int c = 2; c <= 40; c += 2) evens.push_back(c);
    CHECK(change(999, evens) == 0);
    // Adding a coin of 999 gives exactly one combination (that coin alone).
    evens.push_back(999);
    CHECK(change(999, evens) == 1);
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> pool(10);
        std::iota(pool.begin(), pool.end(), 1);
        std::shuffle(pool.begin(), pool.end(), rng());
        pool.resize(rand_int(1, 4));
        const int amount = rand_int(0, 25);
        INFO("amount " << amount << " coins " << pool);
        CHECK(change(amount, pool) == brute(amount, pool));
    }
}
