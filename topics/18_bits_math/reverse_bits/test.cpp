#include <reverse_bits.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <cstdint>
#include <string>

namespace {
// Obviously-correct reference: write 32 binary digits, reverse the string, read it back.
std::uint32_t brute(std::uint32_t n) {
    std::string s(32, '0');
    for (int i = 0; i < 32; ++i)
        if ((n >> (31 - i)) & 1u) s[i] = '1';  // s[0] is the most significant bit
    std::reverse(s.begin(), s.end());
    std::uint32_t r = 0;
    for (char c : s) r = r * 2 + static_cast<std::uint32_t>(c - '0');
    return r;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(reverseBits(1) == 0x80000000u);
    CHECK(reverseBits(0x0000000Fu) == 0xF0000000u);
    CHECK(reverseBits(0xFFFFFFFFu) == 0xFFFFFFFFu);
}

TEST_CASE("edge cases") {
    SUBCASE("zero") { CHECK(reverseBits(0) == 0); }
    SUBCASE("1 maps to the top bit and back") {
        CHECK(reverseBits(1) == 0x80000000u);
        CHECK(reverseBits(0x80000000u) == 1u);
    }
    SUBCASE("all ones") { CHECK(reverseBits(0xFFFFFFFFu) == 0xFFFFFFFFu); }
    SUBCASE("each single bit moves from i to 31 - i") {
        for (int i = 0; i < 32; ++i) {
            CAPTURE(i);
            CHECK(reverseBits(1u << i) == (1u << (31 - i)));
        }
    }
    SUBCASE("leading zeros are kept") { CHECK(reverseBits(0x00000002u) == 0x40000000u); }
    SUBCASE("a known pattern") {
        CHECK(reverseBits(0x00000001u | 0x00000004u) == 0xA0000000u);  // bits 0 and 2 -> bits 31 and 29
        CHECK(reverseBits(0x0000FFFFu) == 0xFFFF0000u);
    }
    SUBCASE("applying it twice gives the original") {
        for (std::uint32_t n : {0u, 1u, 0xDEADBEEFu, 0x12345678u, 0xFFFFFFFFu}) {
            CAPTURE(n);
            CHECK(reverseBits(reverseBits(n)) == n);
        }
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        std::uint32_t n = static_cast<std::uint32_t>(rng()());
        CAPTURE(n);
        CHECK(reverseBits(n) == brute(n));
    }
}
