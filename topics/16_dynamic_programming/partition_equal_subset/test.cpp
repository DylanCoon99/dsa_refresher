#include <partition_equal_subset.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Try every subset: does one of them sum to exactly half of the total?
bool brute(const std::vector<int>& v) {
    const int n = static_cast<int>(v.size());
    int total = 0;
    for (int x : v) total += x;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) sum += v[i];
        if (2 * sum == total) return true;
    }
    return false;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(canPartition({1, 5, 11, 5}));
    CHECK_FALSE(canPartition({1, 2, 3, 5}));
    CHECK_FALSE(canPartition({4}));
}

TEST_CASE("edge cases") {
    SUBCASE("odd total") {
        CHECK_FALSE(canPartition({1, 2, 4}));
        CHECK_FALSE(canPartition({3}));
    }
    SUBCASE("a single element") {
        CHECK_FALSE(canPartition({2}));
        CHECK_FALSE(canPartition({100}));
    }
    SUBCASE("two equal elements") { CHECK(canPartition({7, 7})); }
    SUBCASE("two different elements") { CHECK_FALSE(canPartition({3, 5})); }
    SUBCASE("even total but no half-sum subset") {
        CHECK_FALSE(canPartition({2, 2, 2, 8}));
        CHECK_FALSE(canPartition({1, 1, 6}));
    }
    SUBCASE("every number used once: a big number balanced by many small ones") {
        CHECK(canPartition({6, 1, 1, 1, 1, 1, 1}));
    }
    SUBCASE("all equal") {
        CHECK(canPartition({3, 3, 3, 3}));
        CHECK_FALSE(canPartition({3, 3, 3}));
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 14), 1, 20);
        INFO(v);
        CHECK(canPartition(v) == brute(v));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 199 copies of 100 and one 2: the total 19902 is even, but its half 9951 is odd and every number
    // except the 2 is a multiple of 100 (so every subset sum is even), so the answer is false. Enumerating
    // 2^200 subsets cannot finish.
    std::vector<int> bad(199, 100);
    bad.push_back(2);
    CHECK_FALSE(canPartition(bad));
    // The values 1..100 twice: the total is 10100 and one full copy of 1..100 sums to the half, 5050.
    std::vector<int> good;
    for (int copy = 0; copy < 2; ++copy)
        for (int x = 1; x <= 100; ++x) good.push_back(x);
    CHECK(canPartition(good));
}
