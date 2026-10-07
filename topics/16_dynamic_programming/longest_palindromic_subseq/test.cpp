#include <longest_palindromic_subseq.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <string>

namespace {
// Try every subsequence (2^n masks) and keep the longest palindrome.
int brute(const std::string& s) {
    const int n = static_cast<int>(s.size());
    int best = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        std::string t;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) t += s[i];
        std::string r(t.rbegin(), t.rend());
        if (t == r) best = std::max(best, static_cast<int>(t.size()));
    }
    return best;
}

std::string alternating(const std::string& pair, int n) {
    std::string s;
    for (int i = 0; i < n; ++i) s += pair[i % 2];
    return s;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(longestPalindromeSubseq("bbbab") == 4);
    CHECK(longestPalindromeSubseq("cbbd") == 2);
    CHECK(longestPalindromeSubseq("a") == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("a single char") { CHECK(longestPalindromeSubseq("z") == 1); }
    SUBCASE("all the same") {
        CHECK(longestPalindromeSubseq("aaaa") == 4);
        CHECK(longestPalindromeSubseq("aa") == 2);
    }
    SUBCASE("no repeated characters: the answer is 1") {
        CHECK(longestPalindromeSubseq("abcdef") == 1);
        CHECK(longestPalindromeSubseq("ab") == 1);
    }
    SUBCASE("already a palindrome") {
        CHECK(longestPalindromeSubseq("racecar") == 7);
        CHECK(longestPalindromeSubseq("abba") == 4);
    }
    SUBCASE("the palindrome is not contiguous") {
        CHECK(longestPalindromeSubseq("agbdba") == 5);  // "abdba"
        CHECK(longestPalindromeSubseq("character") == 5);  // "carac"
    }
}

TEST_CASE("randomized vs brute force (length <= 12)") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 12), 'a', 'a' + rand_int(1, 4));
        INFO("s = " << s);
        CHECK(longestPalindromeSubseq(s) == brute(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // (ab)^500: dropping the last character leaves "abab...a" of length 999, which is a palindrome; the whole
    // string is not a palindrome, so the answer is 999.
    CHECK(longestPalindromeSubseq(alternating("ab", 1000)) == 999);
    // a^500 b^500: every a comes before every b, so a subsequence using both letters starts with an a and ends
    // with a b and is not a palindrome. The best is one letter alone: 500.
    CHECK(longestPalindromeSubseq(std::string(500, 'a') + std::string(500, 'b')) == 500);
}
