#include <house_robber_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Every subset of houses; house i is a neighbour of (i + 1) % n. A single house has no neighbour.
int brute(const std::vector<int>& v) {
    const int n = static_cast<int>(v.size());
    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        if (n > 1)
            for (int i = 0; i < n; ++i)
                if ((mask >> i & 1) && (mask >> ((i + 1) % n) & 1)) ok = false;
        if (!ok) continue;
        int sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) sum += v[i];
        if (sum > best) best = sum;
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(rob({2, 3, 2}) == 3);
    CHECK(rob({1, 2, 3, 1}) == 4);
    CHECK(rob({4, 4, 4}) == 4);
}

TEST_CASE("edge cases") {
    SUBCASE("a single house") {
        CHECK(rob({0}) == 0);
        CHECK(rob({9}) == 9);
    }
    SUBCASE("two houses are neighbours") {
        CHECK(rob({3, 8}) == 8);
        CHECK(rob({8, 3}) == 8);
    }
    SUBCASE("three equal houses") { CHECK(rob({5, 5, 5}) == 5); }
    SUBCASE("the best set uses neither end") { CHECK(rob({1, 10, 1, 1}) == 11); }
    SUBCASE("the best set uses the first house") { CHECK(rob({10, 1, 1, 1, 1}) == 11); }
    SUBCASE("the best set uses the last house") { CHECK(rob({1, 1, 1, 1, 10}) == 11); }
    SUBCASE("the line answer would use both ends") { CHECK(rob({7, 1, 1, 7}) == 8); }
    SUBCASE("all zeros") { CHECK(rob({0, 0, 0}) == 0); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 14), 0, 30);
        INFO(v);
        CHECK(rob(v) == brute(v));
    }
}
