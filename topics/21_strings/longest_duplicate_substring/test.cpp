#include <longest_duplicate_substring.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <random>
#include <string>

namespace {
// True if s has a substring of this length that occurs at least twice (overlap allowed).
bool hasDup(const std::string& s, std::size_t len) {
    for (std::size_t i = 0; i + len <= s.size(); ++i)
        if (s.find(s.substr(i, len), i + 1) != std::string::npos) return true;
    return false;
}

std::size_t bruteLen(const std::string& s) {
    for (std::size_t len = s.size(); len >= 1; --len)
        if (hasDup(s, len)) return len;
    return 0;
}

// The answer must occur at least twice in s and have the expected length.
void checkValid(const std::string& s, const std::string& got, std::size_t expectedLen) {
    CHECK_MESSAGE(got.size() == expectedLen, "wrong length: got \"" << got.substr(0, 60) << "\" (" << got.size()
                                                                     << "), expected length " << expectedLen);
    if (!got.empty()) {
        const std::size_t first = s.find(got);
        REQUIRE(first != std::string::npos);
        CHECK_MESSAGE(s.find(got, first + 1) != std::string::npos, "\"" << got.substr(0, 60) << "\" occurs only once");
    }
}
}  // namespace

TEST_CASE("examples") {
    CHECK(longestDupSubstring("banana") == "ana");
    CHECK(longestDupSubstring("abcd") == "");
    CHECK(longestDupSubstring("aaaa") == "aaa");
}

TEST_CASE("edge cases") {
    SUBCASE("single character") {
        CHECK(longestDupSubstring("a") == "");
    }
    SUBCASE("all distinct characters") {
        CHECK(longestDupSubstring("abcdefg") == "");
    }
    SUBCASE("overlapping occurrences") {
        CHECK(longestDupSubstring("aaaa") == "aaa");
        CHECK(longestDupSubstring("aa") == "a");
        CHECK(longestDupSubstring("ababab") == "abab");
    }
    SUBCASE("non-overlapping occurrences") {
        CHECK(longestDupSubstring("abcxabc") == "abc");
    }
    SUBCASE("the answer is not the most frequent substring") {
        // "abc" occurs three times, but "abcd" (twice) is longer.
        CHECK(longestDupSubstring("abcdabcxabcdy") == "abcd");
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 60), 'a', trial % 2 == 0 ? 'b' : 'c');
        INFO("s=" << s);
        checkValid(s, longestDupSubstring(s), bruteLen(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 12000 pseudo-random letters over {a, b}; the longest repeat has length 27 (confirmed with an
    // independent suffix-array computation). Comparing every pair of suffixes is ~7·10^7 pairs, which
    // is far over the 2 s limit under the sanitizers.
    std::mt19937 g(2024);
    std::string s(12'000, 'a');
    for (char& c : s) c = static_cast<char>('a' + ((g() >> 9) & 1));
    checkValid(s, longestDupSubstring(s), 27);
}
