#include <missing_number.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

TEST_CASE("examples") {
    CHECK(missingNumber({3, 0, 1}) == 2);
    CHECK(missingNumber({0, 1}) == 2);
    CHECK(missingNumber({1}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") {
        CHECK(missingNumber({0}) == 1);
        CHECK(missingNumber({1}) == 0);
    }
    SUBCASE("missing 0") { CHECK(missingNumber({4, 2, 1, 3}) == 0); }
    SUBCASE("missing n") { CHECK(missingNumber({2, 0, 1, 3}) == 4); }
    SUBCASE("sorted input, missing a middle value") { CHECK(missingNumber({0, 1, 2, 4, 5}) == 3); }
    SUBCASE("reverse order") { CHECK(missingNumber({5, 4, 3, 1, 0}) == 2); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 60);
        std::vector<int> all(n + 1);
        std::iota(all.begin(), all.end(), 0);
        std::shuffle(all.begin(), all.end(), rng());
        const int missing = all.back();  // after the shuffle, the last element is the one we drop
        all.pop_back();
        // Brute force check of the setup itself: `missing` is the only value of 0..n not in the list.
        int absent = -1;
        for (int v = 0; v <= n; ++v)
            if (std::find(all.begin(), all.end(), v) == all.end()) absent = v;
        REQUIRE(absent == missing);
        CAPTURE(all);
        CHECK(missingNumber(all) == missing);
    }
}
