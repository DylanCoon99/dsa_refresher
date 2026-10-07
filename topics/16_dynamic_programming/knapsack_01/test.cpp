#include <knapsack_01.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <numeric>
#include <vector>

namespace {
using V = std::vector<int>;
using Fn = int (*)(const V&, const V&, int);
struct Impl {
    const char* name;
    Fn fn;
};
const Impl kImpls[] = {{"memo", knapsackMemo}, {"tab", knapsackTab}};

// Enumerate all 2^n subsets.
int brute(const V& wt, const V& val, int cap) {
    const int n = static_cast<int>(wt.size());
    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int w = 0, v = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) {
                w += wt[i];
                v += val[i];
            }
        if (w <= cap && v > best) best = v;
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        CHECK(m.fn({1, 3, 4, 5}, {1, 4, 5, 7}, 7) == 9);
        CHECK(m.fn({5}, {10}, 4) == 0);
        CHECK(m.fn({2, 2}, {3, 4}, 4) == 7);
    }
}

TEST_CASE("edge cases") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        SUBCASE("capacity 0") { CHECK(m.fn({1, 2}, {5, 6}, 0) == 0); }
        SUBCASE("no items") { CHECK(m.fn({}, {}, 10) == 0); }
        SUBCASE("an item heavier than the capacity is skipped") {
            CHECK(m.fn({10, 2}, {100, 3}, 5) == 3);
        }
        SUBCASE("every item fits") { CHECK(m.fn({1, 2, 3}, {10, 20, 30}, 100) == 60); }
        SUBCASE("exact fit") { CHECK(m.fn({3, 4}, {5, 6}, 7) == 11); }
        SUBCASE("greedy by value per weight is wrong") {
            // Ratios 6, 5, 4: greedy takes the first two (weight 30, value 160) and the third no longer
            // fits; the best is the last two (weight 50, value 220).
            CHECK(m.fn({10, 20, 30}, {60, 100, 120}, 50) == 220);
        }
        SUBCASE("an item cannot be used twice") { CHECK(m.fn({1}, {5}, 10) == 5); }
        SUBCASE("zero-value items") { CHECK(m.fn({1, 1}, {0, 0}, 5) == 0); }
    }
}

TEST_CASE("randomized vs brute force (n <= 15)") {
    for (int trial = 0; trial < 250; ++trial) {
        const int n = rand_int(0, 15);
        V wt = rand_vec(n, 1, 12), val = rand_vec(n, 0, 20);
        const int cap = rand_int(0, 40);
        const int expected = brute(wt, val, cap);
        for (const Impl& m : kImpls) {
            INFO(m.name);
            CHECK(m.fn(wt, val, cap) == expected);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 100 items with weight = value = 100..199 and capacity 10^4. With k items the reachable totals form
    // an unbroken range [100k + k(k-1)/2, 199k - k(k-1)/2]; for k = 60 that is [7770, 10170], which
    // contains 10^4, and a total above the capacity is not allowed, so the best value is exactly 10^4.
    V wt(100);
    std::iota(wt.begin(), wt.end(), 100);
    CHECK(knapsackTab(wt, wt, 10000) == 10000);
    CHECK(knapsackMemo(wt, wt, 10000) == 10000);
}
