#include <longest_palindromic_substring.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <string>

namespace {
bool isPal(const std::string& t) {
    return std::equal(t.begin(), t.begin() + t.size() / 2, t.rbegin());
}

std::size_t bruteMax(const std::string& s) {
    std::size_t best = 0;
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t len = 1; i + len <= s.size(); ++len)
            if (len > best && isPal(s.substr(i, len))) best = len;
    return best;
}

// Checks the three properties of a valid answer.
void checkValid(const std::string& s, const std::string& got, std::size_t expectedLen) {
    CHECK_MESSAGE(got.size() == expectedLen, "wrong length for s=" << s << ": got \"" << got << "\"");
    CHECK_MESSAGE(s.find(got) != std::string::npos, "\"" << got << "\" is not a substring of " << s);
    CHECK_MESSAGE(isPal(got), "\"" << got << "\" is not a palindrome");
}
}  // namespace

TEST_CASE("examples") {
    const std::string r = longestPalindrome("babad");
    CHECK((r == "bab" || r == "aba"));
    CHECK(longestPalindrome("cbbd") == "bb");
    CHECK(longestPalindrome("a") == "a");
}

TEST_CASE("edge cases") {
    SUBCASE("single character") {
        CHECK(longestPalindrome("z") == "z");
    }
    SUBCASE("no repeated characters: any single character") {
        const std::string got = longestPalindrome("abcd");
        checkValid("abcd", got, 1);
    }
    SUBCASE("even-length palindromes") {
        CHECK(longestPalindrome("abba") == "abba");
        CHECK(longestPalindrome("xabbay") == "abba");
        CHECK(longestPalindrome("cbbd") == "bb");
    }
    SUBCASE("odd-length palindrome in the middle") {
        CHECK(longestPalindrome("xyracecarz") == "racecar");
    }
    SUBCASE("all the same character") {
        CHECK(longestPalindrome("aaaa") == "aaaa");
        CHECK(longestPalindrome("aaaaa") == "aaaaa");
    }
    SUBCASE("palindrome at the start and at the end") {
        CHECK(longestPalindrome("abacdefg") == "aba");
        CHECK(longestPalindrome("defgaba") == "aba");
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 30), 'a', trial % 2 == 0 ? 'b' : 'c');
        INFO("s=" << s);
        checkValid(s, longestPalindrome(s), bruteMax(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 'a' x 5000: the whole string is the answer. Checking every substring is O(n^3).
    const std::string s(5000, 'a');
    CHECK(longestPalindrome(s) == s);
}
