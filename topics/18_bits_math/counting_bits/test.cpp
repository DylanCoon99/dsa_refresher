#include <counting_bits.hpp>

#include <doctest.h>
#include <printing.hpp>

#include <bit>
#include <vector>

TEST_CASE("examples") {
    CHECK(countBits(2) == std::vector<int>{0, 1, 1});
    CHECK(countBits(5) == std::vector<int>{0, 1, 1, 2, 1, 2});
    CHECK(countBits(0) == std::vector<int>{0});
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0") { CHECK(countBits(0) == std::vector<int>{0}); }
    SUBCASE("n = 1") { CHECK(countBits(1) == std::vector<int>{0, 1}); }
    SUBCASE("n is a power of two") {
        auto got = countBits(16);
        REQUIRE(got.size() == 17);
        CHECK(got[15] == 4);
        CHECK(got[16] == 1);
    }
    SUBCASE("n = 8") { CHECK(countBits(8) == std::vector<int>{0, 1, 1, 2, 1, 2, 2, 3, 1}); }
}

TEST_CASE("against std::popcount for every i up to n") {
    for (int n : {3, 7, 8, 9, 100, 1023, 1024, 5000}) {
        auto got = countBits(n);
        REQUIRE(got.size() == static_cast<std::size_t>(n) + 1);
        for (int i = 0; i <= n; ++i) {
            if (got[i] != std::popcount(static_cast<unsigned>(i))) {
                CAPTURE(n);
                CAPTURE(i);
                CHECK(got[i] == std::popcount(static_cast<unsigned>(i)));
                break;
            }
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // This checks size and values at n = 10^7. A per-number popcount loop is also fast enough
    // (the O(n) recurrence is the learning target, not something the timeout enforces).
    const int n = 10'000'000;
    auto got = countBits(n);
    REQUIRE(got.size() == static_cast<std::size_t>(n) + 1);
    bool all_match = true;
    for (int i = 0; i <= n && all_match; ++i)
        if (got[i] != std::popcount(static_cast<unsigned>(i))) all_match = false;
    CHECK(all_match);
}
