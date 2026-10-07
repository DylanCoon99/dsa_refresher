#include <coin_change.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

namespace {
using Fn = int (*)(const std::vector<int>&, int);
struct Impl {
    const char* name;
    Fn fn;
};
const Impl kImpls[] = {{"memo", coinChangeMemo}, {"tab", coinChangeTab}};

// Plain recursion with no cache: obviously correct, exponential, fine for tiny amounts.
int brute(const std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    int best = -1;
    for (int c : coins) {
        if (c > amount) continue;
        int sub = brute(coins, amount - c);
        if (sub >= 0 && (best < 0 || sub + 1 < best)) best = sub + 1;
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        CHECK(m.fn({1, 2, 5}, 11) == 3);
        CHECK(m.fn({2}, 3) == -1);
        CHECK(m.fn({1, 3, 4}, 6) == 2);
    }
}

TEST_CASE("edge cases") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        SUBCASE("amount 0 needs no coins") {
            CHECK(m.fn({1, 2, 5}, 0) == 0);
            CHECK(m.fn({7}, 0) == 0);
        }
        SUBCASE("impossible") {
            CHECK(m.fn({2, 4}, 7) == -1);
            CHECK(m.fn({5, 10}, 3) == -1);
        }
        SUBCASE("greedy fails") {
            CHECK(m.fn({1, 3, 4}, 6) == 2);
            CHECK(m.fn({1, 5, 6, 9}, 11) == 2);  // 5 + 6; greedy 9 + 1 + 1 uses 3
        }
        SUBCASE("a coin larger than the amount is ignored") {
            CHECK(m.fn({100, 1}, 3) == 3);
            CHECK(m.fn({100, 2}, 4) == 2);
        }
        SUBCASE("amount equal to one coin") { CHECK(m.fn({3, 7, 11}, 7) == 1); }
        SUBCASE("coin order does not matter") { CHECK(m.fn({5, 1, 2}, 11) == 3); }
        SUBCASE("single coin 1") { CHECK(m.fn({1}, 37) == 37); }
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 250; ++trial) {
        std::vector<int> pool(12);
        for (int i = 0; i < 12; ++i) pool[i] = i + 1;
        std::shuffle(pool.begin(), pool.end(), rng());
        pool.resize(rand_int(1, 4));
        const int amount = rand_int(0, 20);
        const int expected = brute(pool, amount);
        for (const Impl& m : kImpls) {
            INFO(m.name);
            CHECK(m.fn(pool, amount) == expected);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // {1,2,5}: the best is as many 5s as fit. 10000 = 2000 * 5; 1000 = 200 * 5.
    CHECK(coinChangeTab({1, 2, 5}, 10000) == 2000);
    CHECK(coinChangeMemo({1, 2, 5}, 1000) == 200);
    // Only even coins: an odd amount is unreachable, but every smaller state still has to be explored.
    CHECK(coinChangeTab({2, 4, 6}, 9999) == -1);
    CHECK(coinChangeMemo({2, 4, 6}, 999) == -1);
}
