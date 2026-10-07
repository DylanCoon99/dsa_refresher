#include <target_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Try every sign assignment (bit i set = '-').
int brute(const std::vector<int>& v, int target) {
    const int n = static_cast<int>(v.size());
    int count = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i) sum += (mask >> i & 1) ? -v[i] : v[i];
        if (sum == target) ++count;
    }
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(findTargetSumWays({1, 1, 1, 1, 1}, 3) == 5);
    CHECK(findTargetSumWays({1}, 1) == 1);
    CHECK(findTargetSumWays({0, 0, 1}, 1) == 4);
}

TEST_CASE("edge cases") {
    SUBCASE("zeros double the count") {
        CHECK(findTargetSumWays({0, 0, 1}, 1) == 4);
        CHECK(findTargetSumWays({0}, 0) == 2);
        CHECK(findTargetSumWays({0, 0, 0, 0}, 0) == 16);
        CHECK(findTargetSumWays(std::vector<int>(20, 0), 0) == (1 << 20));
    }
    SUBCASE("unreachable target") {
        CHECK(findTargetSumWays({1, 2, 3}, 7) == 0);   // above the total
        CHECK(findTargetSumWays({1, 2, 4}, 2) == 0);   // wrong parity: total 7 is odd, target even
        CHECK(findTargetSumWays({2, 4}, 3) == 0);
        CHECK(findTargetSumWays({1}, 2) == 0);
    }
    SUBCASE("negative target") {
        CHECK(findTargetSumWays({1}, -1) == 1);
        CHECK(findTargetSumWays({1, 1, 1, 1, 1}, -3) == 5);
        CHECK(findTargetSumWays({1, 2, 3}, -6) == 1);
        CHECK(findTargetSumWays({1, 2, 3}, -7) == 0);
    }
    SUBCASE("target equal to the full sum") { CHECK(findTargetSumWays({1, 2, 3}, 6) == 1); }
    SUBCASE("target 0") {
        CHECK(findTargetSumWays({1, 1}, 0) == 2);
        CHECK(findTargetSumWays({1, 2, 3}, 0) == 2);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 12), 0, 9);
        int total = 0;
        for (int x : v) total += x;
        const int target = rand_int(-total - 2, total + 2);
        INFO(v << " target " << target);
        CHECK(findTargetSumWays(v, target) == brute(v, target));
    }
}
