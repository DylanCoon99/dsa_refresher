#include <palindromic_substrings.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <string>

namespace {
int brute(const std::string& s) {
    int count = 0;
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t len = 1; i + len <= s.size(); ++len) {
            const std::string t = s.substr(i, len);
            if (std::equal(t.begin(), t.begin() + t.size() / 2, t.rbegin())) ++count;
        }
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(countSubstrings("abc") == 3);
    CHECK(countSubstrings("aaa") == 6);
    CHECK(countSubstrings("abba") == 6);
}

TEST_CASE("edge cases") {
    SUBCASE("single character") {
        CHECK(countSubstrings("a") == 1);
    }
    SUBCASE("two characters") {
        CHECK(countSubstrings("aa") == 3);
        CHECK(countSubstrings("ab") == 2);
    }
    SUBCASE("even and odd centers together") {
        CHECK(countSubstrings("abab") == 6);
        CHECK(countSubstrings("aabaa") == 9);
    }
    SUBCASE("all the same character") {
        CHECK(countSubstrings("aaaa") == 10);
        CHECK(countSubstrings("aaaaaa") == 21);
    }
    SUBCASE("no repeated characters") {
        CHECK(countSubstrings("abcdef") == 6);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 30), 'a', trial % 2 == 0 ? 'b' : 'c');
        INFO("s=" << s);
        CHECK(countSubstrings(s) == brute(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 'a' x 5000: every substring is a palindrome, so the answer is n(n+1)/2 = 12502500.
    // Checking each substring from scratch is O(n^3).
    CHECK(countSubstrings(std::string(5000, 'a')) == 12'502'500);
}
