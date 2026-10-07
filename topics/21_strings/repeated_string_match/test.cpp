#include <repeated_string_match.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <string>

namespace {
int brute(const std::string& a, const std::string& b) {
    // b can start inside the first copy, so it fits within ceil(|b|/|a|) + 1 copies if it fits at all.
    std::string rep;
    for (std::size_t k = 1; k <= b.size() / a.size() + 2; ++k) {
        rep += a;
        if (rep.find(b) != std::string::npos) return static_cast<int>(k);
    }
    return -1;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(repeatedStringMatch("abcd", "cdabcdab") == 3);
    CHECK(repeatedStringMatch("abc", "bc") == 1);
    CHECK(repeatedStringMatch("abc", "acb") == -1);
}

TEST_CASE("edge cases") {
    SUBCASE("b already inside a") {
        CHECK(repeatedStringMatch("abcd", "abcd") == 1);
        CHECK(repeatedStringMatch("abcd", "bc") == 1);
        CHECK(repeatedStringMatch("a", "a") == 1);
    }
    SUBCASE("impossible") {
        CHECK(repeatedStringMatch("abc", "d") == -1);
        CHECK(repeatedStringMatch("abc", "cba") == -1);
        CHECK(repeatedStringMatch("a", "aab") == -1);
    }
    SUBCASE("needs the boundary wrap") {
        CHECK(repeatedStringMatch("abcd", "cdabcdab") == 3);
        CHECK(repeatedStringMatch("abcd", "dab") == 2);
        CHECK(repeatedStringMatch("abc", "cabcabca") == 4);
    }
    SUBCASE("exact multiple, no extra copy needed") {
        CHECK(repeatedStringMatch("ab", "ababab") == 3);
        CHECK(repeatedStringMatch("a", "aaaaa") == 5);
    }
    SUBCASE("b longer than a but not a repetition") {
        CHECK(repeatedStringMatch("abab", "ababa") == 2);
        CHECK(repeatedStringMatch("ab", "aabb") == -1);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        const std::string a = rand_string(rand_int(1, 5), 'a', 'b');
        std::string b;
        if (trial % 2 == 0) {
            // Cut b out of a repeated string so that real matches are common.
            std::string rep;
            while (rep.size() < 30) rep += a;
            const int start = rand_int(0, static_cast<int>(a.size()) - 1);
            b = rep.substr(start, rand_int(1, 14));
            if (trial % 4 == 0 && !b.empty()) b.back() = (b.back() == 'a') ? 'b' : 'a';
        } else {
            b = rand_string(rand_int(1, 10), 'a', 'b');
        }
        INFO("a=" << a << " b=" << b);
        CHECK(repeatedStringMatch(a, b) == brute(a, b));
    }
}
