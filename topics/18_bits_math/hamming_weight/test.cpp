#include <hamming_weight.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <cstdint>

namespace {
// Obviously-correct reference: look at each of the 32 bits.
int brute(std::uint32_t n) {
    int count = 0;
    for (int bit = 0; bit < 32; ++bit)
        if ((n >> bit) & 1u) ++count;
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(hammingWeight(11) == 3);
    CHECK(hammingWeight(128) == 1);
    CHECK(hammingWeight(0xFFFFFFFFu) == 32);
}

TEST_CASE("edge cases") {
    SUBCASE("zero") { CHECK(hammingWeight(0) == 0); }
    SUBCASE("all bits set") { CHECK(hammingWeight(0xFFFFFFFFu) == 32); }
    SUBCASE("every power of two has one set bit") {
        for (int k = 0; k < 32; ++k) {
            CAPTURE(k);
            CHECK(hammingWeight(1u << k) == 1);
        }
    }
    SUBCASE("every power of two minus one has k set bits") {
        for (int k = 1; k < 32; ++k) {
            CAPTURE(k);
            CHECK(hammingWeight((1u << k) - 1) == k);
        }
    }
    SUBCASE("high bit only (the sign bit when read as int)") { CHECK(hammingWeight(0x80000000u) == 1); }
    SUBCASE("alternating bits") {
        CHECK(hammingWeight(0xAAAAAAAAu) == 16);
        CHECK(hammingWeight(0x55555555u) == 16);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        std::uint32_t n = static_cast<std::uint32_t>(rng()());
        CAPTURE(n);
        CHECK(hammingWeight(n) == brute(n));
    }
}
