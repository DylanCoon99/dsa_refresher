#include <house_robber.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Try every subset of houses and keep the best one that has no two neighbours.
int brute(const std::vector<int>& v) {
    const int n = static_cast<int>(v.size());
    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (mask & (mask >> 1)) continue;  // two adjacent bits set
        int sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) sum += v[i];
        if (sum > best) best = sum;
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(rob({1, 2, 3, 1}) == 4);
    CHECK(rob({2, 7, 9, 3, 1}) == 12);
    CHECK(rob({5}) == 5);
}

TEST_CASE("edge cases") {
    SUBCASE("a single house") {
        CHECK(rob({0}) == 0);
        CHECK(rob({42}) == 42);
    }
    SUBCASE("two houses: take the larger") {
        CHECK(rob({3, 9}) == 9);
        CHECK(rob({9, 3}) == 9);
        CHECK(rob({4, 4}) == 4);
    }
    SUBCASE("alternating values") {
        CHECK(rob({5, 1, 5, 1, 5}) == 15);
        CHECK(rob({1, 5, 1, 5, 1, 5}) == 15);
    }
    SUBCASE("skipping two in a row is sometimes best") { CHECK(rob({6, 1, 1, 6}) == 12); }
    SUBCASE("all zeros") { CHECK(rob({0, 0, 0, 0}) == 0); }
    SUBCASE("a big middle house") { CHECK(rob({2, 100, 2}) == 100); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 15), 0, 30);
        INFO(v);
        CHECK(rob(v) == brute(v));
    }
}
